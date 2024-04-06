package com.MyActivity;
import org.qtproject.qt.android.bindings.QtActivity;
import org.qtproject.qt.android.QtNative;
import org.qtproject.qt.android.multimedia.QtAudioDeviceManager;
import java.io.ByteArrayOutputStream;
import android.os.Handler;
import android.os.Message;
import android.os.Bundle;
import android.os.Environment;
import android.os.Build;
import android.app.Activity;
import android.app.UiModeManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.NotificationChannel;
import android.content.Context;
import android.content.res.Configuration;
import android.content.Intent;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.pm.PackageManager;
import android.content.pm.ApplicationInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.graphics.Paint;
import android.graphics.Canvas;
import android.graphics.drawable.BitmapDrawable;
import android.provider.Settings;
import android.provider.MediaStore;
import android.widget.Toast;
import android.view.WindowManager;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.Window;
import android.util.Log;
import android.net.Uri;
//import androidx.core.content.FileProvider;
public class MainActivity extends org.qtproject.qt.android.bindings.QtActivity{
    private static MainActivity m_instance;
    //public native void onConfigurationChanged(Configuration newConfig);

    public static native void onConfigurationChangedmirror(Configuration newConfig);
    @Override
    public void onConfigurationChanged(Configuration newConfig)
    {
        //QtNative.activity()
        super.onConfigurationChanged(newConfig);
        m_instance.onConfigurationChangedmirror(newConfig);
        //super.onConfigurationChanged(newConfig);
    }
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }

    private static Handler m_handler = new Handler() {
         @Override
         public void handleMessage(Message msg)
         {
             switch (msg.what) {
             case 1:
                 Toast toast = Toast.makeText(m_instance,(String)msg.obj, Toast.LENGTH_SHORT);
                 toast.show();
                 break;
             };
         }
     };
     public MainActivity()
     {
          m_instance = this;
     }
     public static void makeToast(String s)
     {
          m_handler.sendMessage(m_handler.obtainMessage(1, s));
     }
 public static Bitmap getApplicationIcon()
      {
          Bitmap icon;
          int iconId = QtNative.activity().getApplicationInfo().icon;
          if(iconId == 0)
          {
              iconId = android.R.drawable.sym_def_app_icon;
              Drawable drawable = QtNative.activity().getResources().getDrawable(android.R.drawable.sym_def_app_icon, null);
              icon = Bitmap.createBitmap(drawable.getIntrinsicWidth(), drawable.getIntrinsicHeight(), Bitmap.Config.ARGB_8888);
              Canvas canvas = new Canvas(icon);
              drawable.setBounds(0, 0, canvas.getWidth(), canvas.getHeight());
              drawable.draw(canvas);
          }
          else
          {
              icon = BitmapFactory.decodeResource(QtNative.activity().getResources(), iconId);
          }
          return icon;
      }
      public static void setFullScreen()
      {
          m_instance.getWindow().getDecorView().setSystemUiVisibility(
          View.SYSTEM_UI_FLAG_IMMERSIVE
                    | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                    | View.SYSTEM_UI_FLAG_FULLSCREEN
                    | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                    | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                    | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                    | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
          );
          m_instance.getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
//          if (Build.VERSION.SDK_INT >= 19 && Build.VERSION.SDK_INT < 21) {
//              m_instance.getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS
//                      | WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
//          }
//          if (Build.VERSION.SDK_INT >= 19) {
//          }
//          if (Build.VERSION.SDK_INT >= 21) {
//              m_instance.getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS
//                      | WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
//              m_instance.getWindow().setStatusBarColor(Color.TRANSPARENT);
//              m_instance.getWindow().setNavigationBarColor(Color.TRANSPARENT);
//          }
//      m_instance.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
      }
// public static byte getApplicationIconArray()
// {
//     Bitmap icon;
//     int iconId = QtNative.activity().getApplicationInfo().icon;
//     if(iconId == 0)
//     {
//         iconId = android.R.drawable.sym_def_app_icon;
//         Drawable drawable = QtNative.activity().getResources().getDrawable(android.R.drawable.sym_def_app_icon, null);
//         icon = Bitmap.createBitmap(drawable.getIntrinsicWidth(), drawable.getIntrinsicHeight(), Bitmap.Config.ARGB_8888);
//         Canvas canvas = new Canvas(icon);
//         drawable.setBounds(0, 0, canvas.getWidth(), canvas.getHeight());
//         drawable.draw(canvas);
//     }
//     else
//     {
//         icon = BitmapFactory.decodeResource(QtNative.activity().getResources(), iconId);
//     }
//     ByteArrayOutputStream baos = new ByteArrayOutputStream();
//     icon.compress(Bitmap.CompressFormat.PNG, 100, baos);
//     return baos.toByteArray();
// }
     public static void makeNotification()
     {
         NotificationManager m_notificationManager = (NotificationManager)m_instance.getSystemService(Context.NOTIFICATION_SERVICE);

         Notification.Builder m_builder;
         if(android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O)
         {
             int importance = NotificationManager.IMPORTANCE_DEFAULT;
             NotificationChannel notificationChannel;
             notificationChannel = new NotificationChannel("Qt", "Qt Notifier", importance);
             m_notificationManager.createNotificationChannel(notificationChannel);
             m_builder = new Notification.Builder(m_instance, notificationChannel.getId());
         }
         else
         {
             m_builder = new Notification.Builder(m_instance);
         }

         Intent intent = new Intent(m_instance, m_instance.getClass());
         PendingIntent contentIntent = PendingIntent.getActivity(m_instance, 0, intent,PendingIntent.FLAG_UPDATE_CURRENT|PendingIntent.FLAG_MUTABLE);
         Bitmap icon;
         int iconId = m_instance.getApplicationInfo().icon;
         if(iconId == 0)
         {
             iconId = android.R.drawable.sym_def_app_icon;//android.R.drawable.ic_menu_save
             Drawable drawable = m_instance.getResources().getDrawable(android.R.drawable.sym_def_app_icon, null);
             icon = Bitmap.createBitmap(drawable.getIntrinsicWidth(), drawable.getIntrinsicHeight(), Bitmap.Config.ARGB_8888);
             //Canvas canvas = new Canvas(icon);
             //drawable.setBounds(0, 0, canvas.getWidth(), canvas.getHeight());
             //drawable.draw(canvas);
         }
         else
         {
             icon = BitmapFactory.decodeResource(m_instance.getResources(), iconId);
         }
         m_builder.setSmallIcon(iconId)
                 .setLargeIcon(icon)
                 .setContentTitle("A message from Qt!")
                 .setContentText("message")
                 .setDefaults(Notification.DEFAULT_SOUND)
                 .setColor(Color.GREEN)
                 .setAutoCancel(true)
                 .setContentIntent(contentIntent)
                 .setOngoing(false);

         m_notificationManager.notify(0, m_builder.build());
     }
     public static void setNotification(Activity activity,String title,String content,boolean autocancel,boolean ongoing)
     {
         NotificationManager notificationManager = (NotificationManager)activity.getSystemService(Context.NOTIFICATION_SERVICE);

         Notification.Builder builder;
         if(android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O)
         {
             int importance = NotificationManager.IMPORTANCE_DEFAULT;
             NotificationChannel notificationChannel;
             notificationChannel = new NotificationChannel("Soviet-Ball", "MyNotifier", importance);
             notificationManager.createNotificationChannel(notificationChannel);
             builder = new Notification.Builder(activity, notificationChannel.getId());
         }
         else
         {
             builder = new Notification.Builder(activity);
         }

         Intent intent = new Intent(activity, activity.getClass());
         PendingIntent contentIntent = PendingIntent.getActivity(activity, 0, intent,PendingIntent.FLAG_UPDATE_CURRENT|PendingIntent.FLAG_MUTABLE);
         Bitmap icon;
         int iconId = activity.getApplicationInfo().icon;
         if(iconId == 0)
         {
             iconId = android.R.drawable.sym_def_app_icon;
             Drawable drawable = activity.getResources().getDrawable(android.R.drawable.sym_def_app_icon, null);
             icon = Bitmap.createBitmap(drawable.getIntrinsicWidth(), drawable.getIntrinsicHeight(), Bitmap.Config.ARGB_8888);
             Canvas canvas = new Canvas(icon);
             drawable.setBounds(0, 0, canvas.getWidth(), canvas.getHeight());
             drawable.draw(canvas);
         }
         else
         {
             icon = BitmapFactory.decodeResource(activity.getResources(), iconId);
         }
         builder.setSmallIcon(iconId)
                .setLargeIcon(icon)
                .setContentTitle(title)
                .setContentText(content)
                .setDefaults(Notification.DEFAULT_SOUND)
                .setColor(Color.GREEN)
                .setAutoCancel(autocancel)
                .setContentIntent(contentIntent)
                .setOngoing(ongoing);

         notificationManager.notify(0, builder.build());
 }

/*
     Java Fuctions that are no longer used

     public static void create_si(Activity activity,String packagename,String activityname)
     {
         Intent intent = new Intent(Intent.ACTION_MAIN);
         intent.setClassName(packagename,activityname);
         intent.putExtra(packagename,activityname);
         intent.addCategory(Intent.CATEGORY_LAUNCHER);
         intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
         activity.startActivity(intent);
     }
     public static void saveImage(Activity activity,String s)
     {
         Bitmap bitmap = BitmapFactory.decodeFile(s);
         MediaStore.Images.Media.insertImage(activity.getContentResolver(), bitmap, "", "");
         Intent intent = new Intent(Intent.ACTION_MEDIA_MOUNTED, Uri.parse("file://"+ Environment.getExternalStorageDirectory()));
         activity.sendBroadcast(intent);
     }
     public static void ManageAllFile(Activity activity)
     {
         Intent intent = new Intent("android.settings.MANAGE_APP_ALL_FILES_ACCESS_PERMISSION");
         intent.setData(Uri.parse("package:" + activity.getPackageName()));
         activity.startActivity(intent);
     }
     public static void startIntent(Activity activity,String string,int append)
     {
         Intent intent = new Intent(string);
         if(append == 1)
         {
             intent.setData(Uri.parse("package:" + activity.getPackageName()));
         }
         activity.startActivity(intent);
     }
     public static int isDarkMode(Context context)
     {
         int currentNightMode = context.getResources().getConfiguration().uiMode & Configuration.UI_MODE_NIGHT_MASK;
         if(currentNightMode == Configuration.UI_MODE_NIGHT_YES)
         {
             return 1;
         }
         else
         {
             return 0;
         }
     }
*/
}
