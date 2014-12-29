package org.lambdacloud.sdk;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo.State;
import android.util.Log;

public class LambdaNetworkUtil {
    static ConnectivityManager mConnManager = null;
    static String LAMBDACLOUD_SDK = "LAMBDACLOUD_SDK";

    private static void init() {
        Context context = Cocos2dxActivity.getContext();
        if (context != null)
        {
            mConnManager = (ConnectivityManager) context
                    .getSystemService(Context.CONNECTIVITY_SERVICE);
        }
    }

    public static int getInternetConnectionStatus() {
        if (mConnManager == null)
        {
            init();
        }
        
        if (mConnManager != null)
        {
            try
            {
                State state = mConnManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI).getState();
                if (State.CONNECTED == state || State.CONNECTING == state)
                {
                    return 1;
                }
                
                state = mConnManager.getNetworkInfo(ConnectivityManager.TYPE_MOBILE).getState();
                if (State.CONNECTED == state || State.CONNECTING == state)
                {
                    return 2;
                }
            } catch (Exception e) { 
                Log.e(LAMBDACLOUD_SDK, "get exception while getting connection status, detail is " + e.toString());
                return 0;
            }
        }
        
        return 0;
    }
}
