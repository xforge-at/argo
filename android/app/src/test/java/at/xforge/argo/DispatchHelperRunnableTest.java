package at.xforge.argo;

import android.os.Handler;

import org.junit.Test;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;

import at.xforge.argo.DispatchHelperRunnable;
import djinni.MainThreadDispatchQueueHelper;

import static org.junit.Assert.*;
import static org.mockito.Mockito.*;

/**
 * To work on unit tests, switch the Test Artifact in the Build Variants view.
 */

public class DispatchHelperRunnableTest {
    MainThreadDispatchQueueHelper mockHelper = mock(MainThreadDispatchQueueHelper.class);
    Handler mockHandler = mock(Handler.class);
    DispatchHelperRunnable dispatchHelperRunnable = new DispatchHelperRunnable(mockHelper);

    @Test
    public void tickDrainsTheQueue() throws Exception {
        when(mockHelper.waitForItems(anyInt())).thenReturn(true);
        doAnswer(new Answer() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                Object[] args = invocation.getArguments();
                Runnable cb = (Runnable)args[0];
                cb.run();
                return null;
            }
        }).when(mockHandler).post(any(Runnable.class));
        dispatchHelperRunnable.tick(mockHelper, mockHandler);

        verify(mockHelper).drainQueue();
    }
}
