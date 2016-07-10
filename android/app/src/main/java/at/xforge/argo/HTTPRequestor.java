package at.xforge.argo;

import org.apache.commons.io.IOUtils;
import org.apache.commons.lang3.StringUtils;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Executor;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import djinni.Error;
import djinni.HttpRequestor;
import djinni.HttpRequestorCallback;
import djinni.Request;
import djinni.Response;

/**
 * Created by michael on 10.07.16.
 */

public class HTTPRequestor extends HttpRequestor {
    private Executor mExecutor;

    public HTTPRequestor() {
        BlockingQueue<Runnable> workQueue = new LinkedBlockingQueue<Runnable>();
        mExecutor = new ThreadPoolExecutor(1, 20, 60, TimeUnit.SECONDS, workQueue);
    }
    @Override
    public void executeRequest(final Request request, final HttpRequestorCallback callback) {
        mExecutor.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    //Set URL
                    URL url = new URL(request.getUrl());
                    HttpURLConnection connection = (HttpURLConnection)url.openConnection();

                    //Set method
                    connection.setRequestMethod(request.getMethod());

                    //Set header
                    HashMap<String, String> requestHeader;
                    if ((requestHeader = request.getHeader()) != null) {
                        for (String key : requestHeader.keySet()) {
                            String value = requestHeader.get(key);
                            connection.setRequestProperty(key, value);
                        }
                    }

                    //Set body
                    final byte[] bodyToSend;
                    if ((bodyToSend = request.getBody()) != null) {
                        connection.setDoOutput(true);

                        OutputStream os = connection.getOutputStream();
                        os.write(bodyToSend);
                        os.close();
                    }

                    //Send
                    connection.connect();

                    //Get header
                    HashMap<String,String> headerFields = new HashMap<>();
                    for (Map.Entry<String, List<String>> entry : connection.getHeaderFields().entrySet()) {
                        headerFields.put(entry.getKey(), StringUtils.join(entry.getValue(), ",")); //Make Value List to String
                    }

                    //Get body
                    InputStream is = connection.getInputStream();
                    byte[] body = IOUtils.toByteArray(is);

                    Response r = new Response(request, headerFields, body);
                    callback.receiveResponse(r);
                } catch (MalformedURLException e) {
                    callback.receiveError(new Error(e.getMessage()));
                } catch (ProtocolException e) {
                    callback.receiveError(new Error(e.getMessage()));
                } catch (IOException e) {
                    callback.receiveError(new Error(e.getMessage()));
                }
            }
        });
    }
}
