# What Is This?
This is a native binary that allows Unity developers to ask Windows what is the currently default microphone.  Currently Unity doesn't seem to support this, so I wrote this wrapper that asks Windows directly.  This is useful for users who have a computer with more than one microphone and they can set it through the SteamVR audio preferences.

# How To Get Started
* Download the latest release and copy the files from x86 and x86_64 into your Assets/Plugins/x86 and Assets/Plugins/x86_x64 folders respectively
* In Unity, call the function below to get the currently selected microphone using P/Invoke.

```C#
    [DllImport("UnityMicLister", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    private static extern uint GetDefaultMicrophoneName(out IntPtr argument);

    /// <summary>
    /// Gets the friendly name of the microphone that SteamVR has set as the default
    /// </summary>
    /// <returns>null if none found, otherwise it's the name of the default microphone</returns>
    public static string DefaultMicrophoneName()
    {
        IntPtr argument;
        uint result = GetDefaultMicrophoneName(out argument);

        if (result == 0)
        {
            string micName = Marshal.PtrToStringUni(argument);
            return micName;
        }
        else
        {
            Debug.LogError("Failed to query windows for the default microphone");
            return null;
        }
    } 
```
