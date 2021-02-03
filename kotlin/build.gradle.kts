import org.gradle.api.tasks.testing.logging.TestExceptionFormat.FULL
import java.net.URI
import java.util.Date

val GENERATED_SOURCE_DIR = "${project.rootDir}/native/src/generated"
val HOST_ARCH = "${System.getProperty("os.name").toLowerCase().replace("mac os x", "darwin")}-${System.getProperty("os.arch").toLowerCase()}"
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



fun findConfigProperty(name: String): String?
        = (project.findProperty("ffmpeg4kj.$name") ?: project.findProperty(name))?.toString()

val signingSecretKeyRingFile = findConfigProperty("signing.secretKeyRingFile")
val signingPassword = findConfigProperty("signing.password")
val signingKeyId = findConfigProperty("signing.keyId")
val githubToken = findConfigProperty("github.token")
val sonatypeUsername = findConfigProperty("sonatype.username")
val sonatypePassword = findConfigProperty("sonatype.password")

val releaseVersion = !version.toString().endsWith("-SNAPSHOT")
val arch = project.properties["arch"] ?: HOST_ARCH
val buildCmd = if (arch == HOST_ARCH) { "./scripts/build.sh" } else { "./scripts/cross-build.sh" }

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

    classes {
        finalizedBy("buildNativeArchve")
    }

    register("generateNativeHeaders", Task::class) {
        dependsOn("classes")
        inputs.files(sourceSets["main"].output.classesDirs)
        outputs.files(fileTree(GENERATED_SOURCE_DIR))

        doLast {
            exec {
                commandLine(
                    "${project.rootDir}/tools/gjavah.sh",
                    "-d", GENERATED_SOURCE_DIR,
                    "-classpath", (sourceSets["main"].runtimeClasspath + sourceSets["main"].output).filter { it.exists() }.asPath,
                    sourceSets["main"].output.asFileTree.matching { include("**/*.class") }.joinToString(separator = " "))
            }
        }
    }

    register("generateCMakeProjects", Task::class) {
        dependsOn("generateNativeHeaders")
        inputs.files(fileTree("${project.rootDir}/native").matching {
            include("**/CMakeLists.txt")
            include("**/*.cmake")
            exclude("cmake-build-$arch-Release/**")
        })
        outputs.files(file("${project.rootDir}/native/cmake-build-$arch-Release/created-at"))

        doLast {
            exec {
                workingDir("${project.rootDir}/native")
                environment["JAVA_HOME"] = System.getenv("JAVA_HOME")
                commandLine("sh", buildCmd, "-a", arch, "-g")
            }
        }
    }

    register("buildNative", Task::class) {
        dependsOn("generateCMakeProjects")
        inputs.files(fileTree("${project.rootDir}/native").matching {
            include("**/*")
            include("cmake-build-$arch-Release/created-at")
            exclude("**/CMakeLists.txt")
            exclude("**/*.cmake")
            exclude("cmake-build-$arch-Release/**")
        })
        outputs.files(fileTree("${project.rootDir}/native/cmake-build-$arch-Release").matching {
            include("package/**")
        })

        doLast {
            exec {
                workingDir("${project.rootDir}/native")
                environment["JAVA_HOME"] = System.getenv("JAVA_HOME")
                commandLine("sh", buildCmd, "-a", arch, "-b")
            }
        }
    }

    register("buildNativeArchve", Zip::class) {
        dependsOn("buildNative")
        inputs.files(fileTree("${project.rootDir}/native/cmake-build-$arch-Release").matching {
            include("package/**")
        })
        outputs.files(fileTree("${project.rootDir}/native/cmake-build-$arch-Release").matching {
            include("package/**")
        })

        archiveFileName.set("libffmpeg4kj_jni-$arch.zip")
        destinationDirectory.set(file("${project.rootDir}/kotlin/src/main/resources/native/$arch"))
        from("${project.rootDir}/native/cmake-build-$arch-Release/package")
    }

    register("cleanNative", Delete::class) {
        delete(GENERATED_SOURCE_DIR)
        delete("${project.rootDir}/native/cmake-build-$arch-Release")
        delete("${project.rootDir}/kotlin/src/main/resources/native")
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
