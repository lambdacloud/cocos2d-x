package org.lambdacloud.sdk;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo.State;
import android.os.Build;
import android.util.Log;

public class LambdaDeviceUtil {
	static ConnectivityManager mConnManager = null;
	static String LAMBDACLOUD_SDK = "LAMBDACLOUD_SDK";
	static String UNKNOWN = "unknown";

	private static void initConnManager() {
	    try {
    		Context context = Cocos2dxActivity.getContext();
    		if (context != null)
    		{
    			mConnManager = (ConnectivityManager) context
    					.getSystemService(Context.CONNECTIVITY_SERVICE);
    		}
	    } catch (Exception e)
	    {
	        Log.e(LAMBDACLOUD_SDK, "get exception while calling initConnManager, detail is " + e.toString());
	    }
	}
	
	private static String capitalize(String s) {
	    if (s == null || s.length() == 0) {
	        return "";
	    }
	    char first = s.charAt(0);
	    if (Character.isUpperCase(first)) {
	        return s;
	    } else {
	        return Character.toUpperCase(first) + s.substring(1);
	    }
	} 

	public static int getInternetConnectionStatus() {
		if (mConnManager == null)
		{
			initConnManager();
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
	
	public static String getDeviceName() {
	    try
	    {
    	    String manufacturer = Build.MANUFACTURER;
    	    String model = Build.MODEL;
    	    if (model.startsWith(manufacturer)) {
    	        return capitalize(model);
    	    } else {
    	        return capitalize(manufacturer) + " " + model;
    	    }
	    } catch (Exception e){
	        Log.e(LAMBDACLOUD_SDK, "get exception while reading device name, detail is " + e.toString());
	        return UNKNOWN;
	    }
	}
}
