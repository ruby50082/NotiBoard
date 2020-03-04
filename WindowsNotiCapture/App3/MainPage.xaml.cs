using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Foundation.Metadata;
using Windows.Storage;
using Windows.UI.Notifications;
using Windows.UI.Notifications.Management;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// 空白頁項目範本已記錄在 https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x404

namespace App3
{
    /// <summary>
    /// 可以在本身使用或巡覽至框架內的空白頁面。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private async void Button_Click(object sender, RoutedEventArgs e)
        {
            await UpdateNotiFile();

        }

        private int GetNotiType(string AppName)
        {
            switch (AppName)
            {
                case "Google Chrome":
                    return 1;
                case "LINE":
                    return 2;
                case "Skype":
                    return 3;
                case "郵件":
                    return 4;
                case "Youtube":
                    return 5;
                default:
                    return -1;
            }
        }

        private async Task UpdateNotiFile()
        {
            // Check Permissions
            if (!ApiInformation.IsTypePresent("Windows.UI.Notifications.Management.UserNotificationListener"))
            {
                Debug.WriteLine("IsTypePresent: NG");
                return;
            }
            Debug.WriteLine("IsTypePresent: OK");

            UserNotificationListener listener = UserNotificationListener.Current;
            Debug.Write("listener: ");
            Debug.WriteLine(listener);

            while(true)
            {

                // Read Notifications
                try
                {

                    UserNotificationListenerAccessStatus accessStatus = await listener.RequestAccessAsync();

                    Debug.Write("accessStatus: ");
                    Debug.WriteLine(accessStatus);

                    if (accessStatus != UserNotificationListenerAccessStatus.Allowed)
                    {
                        Debug.WriteLine("アクセス拒否");
                        return;
                    }
                    Debug.WriteLine("アクセス許可");

                    IReadOnlyList<UserNotification> notifs = await listener.GetNotificationsAsync(NotificationKinds.Toast);

                    // Write to Download/App3

                    Windows.Storage.StorageFile file = await DownloadsFolder.CreateFileAsync("notifications.txt");

                    // await Windows.Storage.FileIO.WriteTextAsync(file, "Example of writing a string\r\n");

                    // Append a list of strings, one per line, to the file
                    var listOfStrings = new List<string> { };

                    foreach (var n in notifs)
                    {
                        NotificationBinding toastBinding = n.Notification.Visual.GetBinding(KnownNotificationBindings.ToastGeneric);

                        if (toastBinding != null)
                        {
                            IReadOnlyList<AdaptiveNotificationText> textElements = toastBinding.GetTextElements();

                            string titleText = textElements.FirstOrDefault()?.Text;

                            string bodyText = string.Join("\n", textElements.Skip(1).Select(t => t.Text));

                            Debug.Write("Title:");
                            Debug.WriteLine(titleText);
                            Debug.Write("Body:");
                            Debug.WriteLine(bodyText);

                            int MsgType = GetNotiType(n.AppInfo.DisplayInfo.DisplayName);
                            if (MsgType != -1)
                                listOfStrings.Add(String.Format("{0}", MsgType));
                            // await Windows.Storage.FileIO.WriteTextAsync(file, String.Format("{0}, {1}\n", n.AppInfo.DisplayInfo.DisplayName, titleText));
                        }
                    }
                    await Windows.Storage.FileIO.AppendLinesAsync(file, listOfStrings); // each entry in the list is written to the file on its own line.
                    await Task.Delay(TimeSpan.FromSeconds(1));
                }
                catch (Exception ex)
                {

                }
            }
        }
    }
}
