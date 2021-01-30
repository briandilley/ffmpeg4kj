allprojects { project ->
    publishing {
        publications {
            ffmpeg4kj {
                pom {
                    name = rootProject.name.capitalize() + (project.parent ? " ($shortName)" : '')
                    description = project.description
                    url = 'https://github.com/briandilley/ffmpeg4kj'
                    issueManagement {
                        system = 'GitHub'
                        url = 'https://github.com/briandilley/ffmpeg4kj/issues'
                    }
                    ciManagement {
                        system = 'Github Actions'
                        url = 'https://github.com/briandilley/ffmpeg4kj/actions'
                    }
                    inceptionYear = '2013'
                    developers {
                        developer {
                            id = 'briandilley'
                            name = 'Brian Dilley'
                            email = 'brian.dilley@gmail.com.com'
                            url = 'https://github.com/briandilley'
                            timezone = 'America/Los_Angeles'
                        }
                    }
                    licenses {
                        license {
                            name = 'The MIT License (MIT)'
                            url = 'https://github.com/briandilley/ffmpeg4kj/blob/develop/LICENSE'
                            distribution = 'repo'
                            comments = 'A business-friendly OSS license'
                        }
                    }
                    scm {
                        connection = 'scm:git:https://github.com/briandilley/ffmpeg4kj.git'
                        developerConnection = 'git@github.com:briandilley/ffmpeg4kj.git'
                        url = 'https://github.com/briandilley/ffmpeg4kj'
                    }
                    distributionManagement {
                        downloadUrl = 'https://github.com/briandilley/ffmpeg4kj/releases'
                    }
                }
            }
        }
    }
}
