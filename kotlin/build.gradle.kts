import org.gradle.api.tasks.testing.logging.TestExceptionFormat.FULL
import java.net.URI

val GENERATED_SOURCE_DIR = "${project.rootDir}/native/src/generated"
val HOST_ARCH = "${System.getProperty("os.name").toLowerCase().replace("mac os x", "darwin")}-${System.getProperty("os.arch").toLowerCase()}"
val NATIVE_ARCHITECTURES = setOf(
    HOST_ARCH,
    "darwin-x86_64"
    //"linux-x86",
    //"linux-x86_64",
    //"linux-armv6",
    //"linux-armv7",
    //"linux-arm64"
)
val JAVA_TARGET_VERSION = "1.8"

buildscript {
    repositories {
        gradlePluginPortal()
        mavenCentral()
    }
    dependencies {
        classpath("gradle.plugin.net.wooga.gradle:atlas-github:1.0.1")
        classpath("net.researchgate:gradle-release:2.7.0")
        classpath("org.ajoberstar:grgit:2.3.0")
        classpath("org.kohsuke:github-api:1.93")
    }
}

plugins {
    id("org.jetbrains.dokka") version "1.4.20"
    kotlin("jvm") version "1.4.21"
    id("maven-publish")
    jacoco
    idea
    signing
}

fun buildNative(arch: String = HOST_ARCH) {
    val nativeWorkDir = "${project.rootDir}/native/cmake-build-$arch-Release"
    exec {
        workingDir("${project.rootDir}/native")
        environment["JAVA_HOME"] = System.getenv("JAVA_HOME")
        if (arch == HOST_ARCH) {
            commandLine("sh", "./scripts/build.sh", "-a", arch)
        } else {
            commandLine("sh", "./scripts/cross-build.sh", "-a", arch)
        }
    }
    val exit = exec {
        workingDir("${nativeWorkDir}/package")
        commandLine("zip", "-1", "-r", "-u", "${nativeWorkDir}/libffmpeg4kj_jni-${arch}.zip", "./")
        isIgnoreExitValue = true
    }.exitValue
    if (exit !=0 && exit != 12) {
        throw GradleException("Zip exit was not 0 or 12")
    }
}

repositories {
    gradlePluginPortal()
    mavenCentral()
    jcenter()
}

dependencies {

    dokkaHtmlPlugin("org.jetbrains.dokka:kotlin-as-java-plugin:1.4.20")

    //api "org.jetbrains.kotlin:kotlin-reflect:${kotlinVersion}"

    testImplementation("org.mockito:mockito-core:2.+")
    testImplementation("com.nhaarman.mockitokotlin2:mockito-kotlin:2.2.0")
    testImplementation("org.junit.jupiter:junit-jupiter-api:5.7.0")
    testImplementation("org.junit.jupiter:junit-jupiter-engine:5.7.0")
}

group = "com.github.briandilley.ffmpeg4kj"
version = "0.1-SNAPSHOT"
description = """
    Kotlin Java library for FFMpeg. Not a direct wrapper, but an OOP approach.
    Usable with Kotlin, Java, or any other JVM language.
    """.trimIndent()

val releaseVersion = !version.toString().endsWith("-SNAPSHOT")

var documentationJar: Any? = null
var sourcesJar: Any? = null

tasks {

    /**
     * Customize the jar
     */
    jar {
        base.archivesBaseName = "ffmpeg4kj"
    }

    /**
     * Custom logic on test
     */
    test {
        useJUnitPlatform()
        testLogging {
            exceptionFormat 	= FULL
            showExceptions 		= true
            showStackTraces 	= true
            showCauses 			= true
        }
        maxParallelForks = 1
        maxHeapSize = "2g"
        finalizedBy("jacocoTestReport")
    }

    register("generateNativeHeaders", Task::class) {
        inputs.files(sourceSets["main"].allSource)
        outputs.dir(GENERATED_SOURCE_DIR)

        exec {
            commandLine(
                "${project.rootDir}/tools/gjavah.sh",
                "-d", GENERATED_SOURCE_DIR,
                "-classpath", (sourceSets["main"].runtimeClasspath + sourceSets["main"].output).filter { it.exists() }.asPath,
                sourceSets["main"].output.asFileTree.matching { include("**/*.class") }.joinToString(separator = " "))
        }

        finalizedBy("compileNative")
    }

    register("compileNative", Task::class) {
        inputs.files(fileTree("${project.rootDir}/native/src"))
        inputs.files(fileTree(GENERATED_SOURCE_DIR))

        NATIVE_ARCHITECTURES.forEach {
            outputs.dir("${project.rootDir}/native/cmake-build-$it-Release")
            outputs.file("${project.rootDir}/native/cmake-build-$it-Release/libffmpeg4kj_jni-${it}.zip")
            outputs.file("${project.rootDir}/kotlin/src/main/resources/native/${it}/libffmpeg4kj_jni.zip")
        }
        doLast {
            NATIVE_ARCHITECTURES.forEach {
                buildNative(it)
            }
            NATIVE_ARCHITECTURES.forEach {
                File("${project.rootDir}/kotlin/src/main/resources/native").mkdirs()
                val from = File("${project.rootDir}/native/cmake-build-$it-Release/libffmpeg4kj_jni-${it}.zip")
                val to = File("${project.rootDir}/kotlin/src/main/resources/native/${it}/libffmpeg4kj_jni.zip")
                from.copyTo(to, overwrite = true)
            }
        }
    }

    register("cleanNative", Delete::class) {
        delete(GENERATED_SOURCE_DIR)
        NATIVE_ARCHITECTURES.forEach {
            delete("${project.rootDir}/native/cmake-build-$it-Release")
        }
    }

    /**
     * Custom logic on compile
     */
    compileKotlin {
        sourceCompatibility = JAVA_TARGET_VERSION
        targetCompatibility = JAVA_TARGET_VERSION

        kotlinOptions {
            jvmTarget = JAVA_TARGET_VERSION
        }

        finalizedBy("generateNativeHeaders")
    }

    clean {
        finalizedBy("cleanNative")
    }

    jacoco {
        toolVersion = "0.8.5"
    }

    jacocoTestReport {
        dependsOn(test)
        reports {
            xml.isEnabled = true
            csv.isEnabled = false
        }
    }

    val _documentationJar by creating(Jar::class) {
        dependsOn(dokkaHtml)
        archiveClassifier.set("javadoc")
        from(dokkaHtml.get().outputs)
    }
    documentationJar = _documentationJar

    val _sourcesJar by creating(Jar::class) {
        dependsOn(classes)
        archiveClassifier.set("sources")
        from(sourceSets["main"].allSource)
    }
    sourcesJar = _sourcesJar

    artifacts {
        add("archives", documentationJar!!)
        add("archives", sourcesJar!!)
    }

}

fun findConfigProperty(name: String): String?
        = (project.findProperty("ffmpeg4kj.$name") ?: project.findProperty(name))?.toString()

val signingSecretKeyRingFile = findConfigProperty("signing.secretKeyRingFile")
val signingPassword = findConfigProperty("signing.password")
val signingKeyId = findConfigProperty("signing.keyId")
val githubToken = findConfigProperty("github.token")
val sonatypeUsername = findConfigProperty("sonatype.username")
val sonatypePassword = findConfigProperty("sonatype.password")

project.publishing {
    repositories {
        maven {
            name = "sonatype"
            url = URI(if (releaseVersion) {
                "https://oss.sonatype.org/service/local/staging/deploy/maven2/"
            } else {
                "https://oss.sonatype.org/content/repositories/snapshots/"
            })
            credentials {
                username = sonatypeUsername
                password = sonatypePassword
            }
        }
    }

    publications {
        create<MavenPublication>("ffmpeg4kj") {
            from(components["java"])
            artifact(documentationJar!!)
            artifact(sourcesJar!!)

            pom {
                name.set(rootProject.name)
                description.set(project.description)
                url.set("https://github.com/briandilley/ffmpeg4kj")
                issueManagement {
                    system.set("GitHub")
                    url.set("https://github.com/briandilley/ffmpeg4kj/issues")
                }
                ciManagement {
                    system.set("Github Actions")
                    url.set("https://github.com/briandilley/ffmpeg4kj/actions")
                }
                inceptionYear.set("2013")
                developers {
                    developer {
                        id.set("briandilley")
                        name.set("Brian Dilley")
                        email.set("brian.dilley@gmail.com.com")
                        url.set("https://github.com/briandilley")
                        timezone.set("America/Los_Angeles")
                    }
                }
                licenses {
                    license {
                        name.set("The MIT License (MIT)")
                        url.set("https://github.com/briandilley/ffmpeg4kj/blob/develop/LICENSE")
                        distribution.set("repo")
                        comments.set("A business-friendly OSS license")
                    }
                }
                scm {
                    connection.set("scm:git:https://github.com/briandilley/ffmpeg4kj.git")
                    developerConnection.set("git@github.com:briandilley/ffmpeg4kj.git")
                    url.set("https://github.com/briandilley/ffmpeg4kj")
                }
                distributionManagement {
                    downloadUrl.set("https://github.com/briandilley/ffmpeg4kj/releases")
                }
            }
        }
    }
}

project.signing {
    isRequired = releaseVersion && (tasks.withType<PublishToMavenRepository>().find {
        gradle.taskGraph.hasTask(it)
    } != null)

    sign(publishing.publications)
}
