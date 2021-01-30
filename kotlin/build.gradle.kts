import org.gradle.api.tasks.testing.logging.TestExceptionFormat.FULL

val GENERATED_SOURCE_DIR = "${project.rootDir}/native/src/main/generated"
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

plugins {
    id("org.jetbrains.dokka") version "1.4.20"
    kotlin("jvm") version "1.4.10"
    jacoco
    idea
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

    /**
     * Custom logic on compile
     */
    compileKotlin {
        sourceCompatibility = JAVA_TARGET_VERSION
        targetCompatibility = JAVA_TARGET_VERSION

        kotlinOptions {
            jvmTarget = JAVA_TARGET_VERSION
        }

        inputs.files(fileTree("${project.rootDir}/native/src/main"))
        NATIVE_ARCHITECTURES.forEach {
            outputs.files(fileTree("${project.rootDir}/native/cmake-build-$it-Release"))
            outputs.file("${project.rootDir}/native/cmake-build-$it-Release/libffmpeg4kj_jni-${it}.zip")
            outputs.file("${project.rootDir}/kotlin/src/main/resources/native/${it}/libffmpeg4kj_jni.zip")
        }

        doLast {
            exec {
                commandLine(
                    "${project.rootDir}/tools/gjavah.sh",
                    "-d", GENERATED_SOURCE_DIR,
                    "-classpath", (sourceSets["main"].runtimeClasspath + sourceSets["main"].output).filter { it.exists() }.asPath,
                    sourceSets["main"].output.asFileTree.matching { include("**/*.class") }.joinToString(separator = " "))
            }
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

    /**
     * Custom logic on clean
     */
    clean {
        doLast {
            if (file(GENERATED_SOURCE_DIR).exists()) {
                println("Deleting $GENERATED_SOURCE_DIR")
                file(GENERATED_SOURCE_DIR).deleteRecursively()
            }
        }
        NATIVE_ARCHITECTURES.forEach {
            val dir = "${project.rootDir}/native/cmake-build-$it-Release"
            if (file(dir).exists()) {
                println("Deleting $dir")
                file(dir).deleteRecursively()
            }
        }
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

    val documentationJar by creating(Jar::class) {
        dependsOn(dokkaHtml)
        archiveClassifier.set("javadoc")
        from(dokkaHtml.get().outputs)
    }

    val sourcesJar by creating(Jar::class) {
        dependsOn(classes)
        archiveClassifier.set("sources")
        from(sourceSets["main"].allSource)
    }

    artifacts {
        add("archives", documentationJar)
        add("archives", sourcesJar)
    }

}


/*
apply from: 'publishing.gradle'
*/
