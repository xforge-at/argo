package at.xforge.argo.cpp_support

import android.app.Application
import djinni.MainThreadDispatchQueueHelper

/**
 * Created by manu on 06.07.2016.
 */

class ArgoApplication : Application() {
    init {
        System.loadLibrary("Argo_android")
    }

    private val queueHelper = MainThreadDispatchQueueHelper.create()
    private val thread = Thread(DispatchHelperRunnable(queueHelper))

    override fun onCreate() {
        super.onCreate()
        thread.start();
    }

}
