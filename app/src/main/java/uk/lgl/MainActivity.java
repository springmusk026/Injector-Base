package uk.lgl;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.widget.Toast;

import uk.lgl.modmenu.FloatingModMenuService;

public class MainActivity extends Activity {

    static {
        // When you change the lib name, change also on Android.mk file
        // Both must have same name
        System.loadLibrary("Client");
    }

    //To call onCreate, please refer to README.md
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Start(this);

    }

    public static void Start(final Context context) {
        //Check if overlay permission is enabled or not
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && !Settings.canDrawOverlays(context)) {
            Toast.makeText(context.getApplicationContext(), "Overlay permission is required in order to show mod menu. Restart the game after you allow permission", Toast.LENGTH_LONG).show();
            context.startActivity(new Intent("android.settings.action.MANAGE_OVERLAY_PERMISSION",
                    Uri.parse("package:" + context.getPackageName())));
            final Handler handler = new Handler();
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    System.exit(1);
                }
            }, 5000);
            return;
        } else {
            final Handler handler = new Handler();
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    context.startService(new Intent(context, FloatingModMenuService.class));
                }
            }, 500);
        }
    }
}
