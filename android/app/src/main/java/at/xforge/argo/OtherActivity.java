package at.xforge.argo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import djinni.MyRecord;
import djinni.MyRecordGetter;
import djinni.MyRecordGetterDelegate;

public class OtherActivity extends AppCompatActivity {

    private final MyRecordGetter recordGetter = MyRecordGetter.create();
    private final RecordDelegate delegate = new RecordDelegate();

    private class RecordDelegate extends MyRecordGetterDelegate {
        @Override
        public boolean shouldGetRecord() {
            Log.w("HI", "C++ wants to know if we should receive a record");
            return true;
        }

        @Override
        public void receiveRecord(MyRecord record) {
            Log.w("HI", "Receiving a record from C++...");
            Log.w("HI", "ID: " + record.getId());
            for (String text : record.getTexts()) {
                Log.w("HI", text);
            }
            Log.w("HI", "Our optional is also: " + record.getOptionalTest());
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_other);
    }

    @Override
    protected void onStart() {
        super.onStart();

        recordGetter.setDelegate(delegate);
        recordGetter.getAsyncRecord("Hello world from JAVA");
    }

}
