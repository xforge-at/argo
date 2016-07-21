package at.xforge.argo

import android.os.Handler
import android.os.Looper
import djinni.MainThreadDispatchQueueHelper


/**
 * Created by manu on 06.07.2016.
 * Simple class that runs in a background thread to check if there is something on the main queue to execute
 * When an item becomes available, it is posted to the JVM's main thread
 */
class DispatchHelperRunnable(val queueHelper: MainThreadDispatchQueueHelper) : Runnable {
    override fun run() {
        val mainHandler = Handler(Looper.getMainLooper())
        while (true) {
            // Timeout for one frame per 60fps
            // So we leave enough time for others to run in between
            val timeout = 1000/60;
            if (queueHelper.waitForItems(timeout * 1000)) {
                mainHandler.post {
                    queueHelper.drainQueue()
                }
            }
        }
    }
}
