
buildscript {
    repositories {
        gradlePluginPortal()
        mavenCentral()
    }
    dependencies {
        classpath("io.codearte.gradle.nexus:gradle-nexus-staging-plugin:0.22.0")
    }
}

plugins {
    id("io.codearte.nexus-staging") version "0.22.0"
}

fun findConfigProperty(name: String): String?
    = (project.findProperty("ffmpeg4kj.$name") ?: project.findProperty(name))?.toString()

val sonatypeUsername = findConfigProperty("sonatype.username")
val sonatypePassword = findConfigProperty("sonatype.password")
val sonatypeStagingProfileId = findConfigProperty("sonatype.stagingProfileId")

nexusStaging {
    stagingProfileId = sonatypeStagingProfileId
    username = sonatypeUsername
    password = sonatypePassword
}

tasks.withType<io.codearte.gradle.nexus.BaseStagingTask> {
    mustRunAfter(tasks.withType<PublishToMavenRepository>())

    doFirst {
        if (sonatypeStagingProfileId == null) {
            throw javax.naming.ConfigurationException(
                    "Please set the Sonatype staging profile id with project property 'sonatype.stagingProfileId' " +
                            "or 'ffmpeg4kj.sonatype.stagingProfileId'. If both are set, the latter will be effective.")
        }
        if (sonatypeUsername == null) {
            throw javax.naming.ConfigurationException(
                "Please set the Sonatype staging profile id with project property 'sonatype.username' " +
                        "or 'ffmpeg4kj.sonatype.username'. If both are set, the latter will be effective.")
        }
        if (sonatypePassword == null) {
            throw javax.naming.ConfigurationException(
                "Please set the Sonatype staging profile id with project property 'sonatype.password' " +
                        "or 'ffmpeg4kj.sonatype.password'. If both are set, the latter will be effective.")
        }
    }
}
