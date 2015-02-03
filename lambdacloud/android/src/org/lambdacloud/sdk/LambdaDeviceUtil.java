package org.lambdacloud.sdk;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo.State;
import android.os.Build;
import android.telephony.TelephonyManager;
import android.util.Log;

public class LambdaDeviceUtil {
	static ConnectivityManager mConnManager = null;
	static TelephonyManager mTeleManager = null;
	static String LAMBDACLOUD_SDK = "LAMBDACLOUD_SDK";
	static String LAMBDA_NETWORK_STATUS_NOT_REACHABLE = "NOT_REACHABLE";
	static String LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WIFI = "WIFI";
	static String LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WWAN = "WWAN";
	static String LAMBDA_DEVICE_INFO_UNKNOWN = "UNKNOWN";
	
	private static void init() {
	    try {
    		Context context = Cocos2dxActivity.getContext();
    		if (context != null)
    		{
    			mConnManager = (ConnectivityManager) context
    					.getSystemService(Context.CONNECTIVITY_SERVICE);
    			mTeleManager = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE); 
    		}
	    } catch (Exception e)
	    {
	        Log.e(LAMBDACLOUD_SDK, "get exception while initization manager, detail is " + e.toString());
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

	public static String getInternetConnectionStatus() {
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
					return LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WIFI;
				}
				
				state = mConnManager.getNetworkInfo(ConnectivityManager.TYPE_MOBILE).getState();
				if (State.CONNECTED == state || State.CONNECTING == state)
				{
					return LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WWAN;
				}
			} catch (Exception e) { 
				Log.e(LAMBDACLOUD_SDK, "get exception while getting connection status, detail is " + e.toString());
				return LAMBDA_DEVICE_INFO_UNKNOWN;
			}
		}
		
		return LAMBDA_NETWORK_STATUS_NOT_REACHABLE;
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
	        return LAMBDA_DEVICE_INFO_UNKNOWN;
	    }
	}
	
	public static String getOperationInfo()
	{
	    if (mTeleManager == null)
        {
            init();
        }
        
        if (mTeleManager != null)
        {
            try
            {
                return mTeleManager.getNetworkOperatorName();
            } catch (Exception e) { 
                Log.e(LAMBDACLOUD_SDK, "get exception while getting operation name, detail is " + e.toString());
            }
        }
        
        return LAMBDA_DEVICE_INFO_UNKNOWN;
	}
}
