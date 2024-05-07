plugins {
    id("com.android.application")
}

android {
    namespace = "com.example.lab8java"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.example.lab8java"
        minSdk = 30
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
}

dependencies {
//    compileOnly ("com.google.android.wearable:wearable:2.9.0")
    implementation ("androidx.wear:wear:1.3.0")
    implementation ("androidx.appcompat:appcompat:1.6.1")
    implementation ("com.google.android.gms:play-services-wearable:18.1.0")
//    implementation ("androidx.wear:wearable:1.3.0")
}