#include "Includes.h"
#include "Functions.h"
#include <intrin.h>
#pragma comment(lib,"Wtsapi32.lib")

int main(int argc, char* argv[])
{
 
    //-- reference the classes
    Roblox Roblox;
    Functions Functions;

    //-- set the console title
    SetConsoleTitle(_T("Autorestart"));

    //-- user has more than 7.25GB of available ram, has more than 3 open cpu threads and is using windows 8 or newer
    if (!Functions.HasEnoughRam() || !Functions.HasEnoughThreads() || !Functions.WindowsDeployment() > 8.1)  {
        Functions.Log("System Incompatiable", true);
        system("pause");
        exit(0);
    }

    //-- Topmost
    ::SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    ::ShowWindow(GetConsoleWindow(), SW_NORMAL);

    //-- lock window
    Functions.LockWindow();

    //-- setup launch options
    if (argc > 1)
    {
        //-- check launch arguments
        for (int i = 0; i < argc; i++)
        {
            //-- forces you to only be in vip servers
            //-- if (Functions.FindString(std::string(argv[i]).c_str(), "onlyvip")) { Functions.OnlyVIP = true; }

            //-- makes autorestart run drastically slower, improving optimization
            if (Functions.FindString(std::string(argv[i]).c_str(), "safemode")) { Functions.SafeMode = true; }

            //-- minimize roblox instances while waiting to restart
            if (Functions.FindString(std::string(argv[i]).c_str(), "minimizeroblox")) { Functions.MinimizeRoblox = true; }

            //-- attempts to detect common roblox errors and restart when it finds them
            if (Functions.FindString(std::string(argv[i]).c_str(), "detecterrors")) { Functions.DetectErrors = true; }

            //-- attempts to detect synapse x crashes and restart when it finds them
            if (Functions.FindString(std::string(argv[i]).c_str(), "detectsynapse")) { Functions.DetectSynapse = true; }
        }
    }

    //-- create the config if it doesnt exist, otherwise set the variables
    Functions.CreateConfig();

    //-- infinite loop
    while (true) {

        //-- if there are multiple browsers configured
        if (Functions.Browsers.size() > 1)
        {
            //-- if they dont have enough ram for the amount of requested instances then dont let them crash their pc with stupidity
            if ((2500 * (Functions.Browsers.size())) / 1024 > Functions.GetRam())
            {
                Functions.Log("You don't have the memory to run these many instances. Stupid.", true);
                system("pause");
                exit(0);
            }

            //-- set the console title to the multifarm one
            SetConsoleTitle(_T("Autorestart (Multi)"));

            //-- unlock instances
            Roblox.Unlock();
        }

        //-- kill roblox
        Roblox.Kill();

        //-- kill the browsers
        Functions.KillBrowsers();

        //-- open the instances
        Functions.RunBrowsers();
        Functions.Debounce(5, 1);

        //-- animation
        auto start = std::chrono::steady_clock::now();
        float A = 0, B = 0;
        float i, j;
        int k;
        int r = 0;
        int log = 0;
        float z[1760];
        char b[1760];

        std::cout << "\x1b[2J";

        //-- while (now - start) <= time
        while (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - start).count() <= Functions.RestartTime) {

            if (Functions.MinimizeRoblox && FindWindow(NULL, "Roblox"))
            {
                for (int i = 0; i < Functions.CountInstances(); i++) {
                    ShowWindow(FindWindow(NULL, "Roblox"), SW_FORCEMINIMIZE);
                }
            }

            //-- attempt to detect errors
            if (Functions.DetectSynapse && FindWindow(NULL, "Synapse X - Crash Reporter") || Functions.DetectErrors && Roblox.FindError())
            {
                Roblox.Kill();
                Functions.KillBrowsers();
                Functions.RunBrowsers();
                Functions.Debounce(10, 1);
            }

            //-- math
            memset(b, 32, 1760);
            memset(z, 0, 7040);
            for (j = 0; j < 6.28; j += 0.07)
            {
                for (i = 0; i < 6.28; i += 0.02)
                {
                    float c = sin(i);
                    float d = cos(j);
                    float e = sin(A);
                    float f = sin(j);
                    float g = cos(A);
                    float h = d + 2;
                    float D = 1 / (c * h * e + f * g + 5);
                    float l = cos(i);
                    float m = cos(B);
                    float n = sin(B);
                    float t = c * h * g - f * e;
                    int x = 40 + 30 * D * (l * h * m - t * n);
                    int y = 12 + 15 * D * (l * h * n + t * m);
                    int o = x + 80 * y;
                    int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                    if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o])
                    {
                        z[o] = D;
                        b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                    }
                }
            }
            std::cout << "\x1b[H";

            //-- rotation
            for (k = 0; k < 1761; k++)
            {   
                putchar(k % 80 ? b[k] : 10);
                A += 0.00004;
                B += 0.00002;
            }

            //-- create space for text at bottom
            for (int i = 0; i <= 2; i++)
            {
                std::cout << "\n";
            }

            //-- buffer to hold the reminaing time
            std::string msg = "(" + std::to_string(Functions.RestartTime - std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - start).count() + 1) + " minutes)";
            //-- push the log
            Functions.Log(msg);

            r++;
            switch (r)
            {
                case 800: {
                    r = 0;
                    break;
                }

                default: {
                    break;
                }
            }

            //-- wait microseconds
            Functions._usleep(10000);
        }

        //-- kill roblox once time has been met
        Roblox.Kill();

        //-- push the log and then jump to beginning of stack
        Functions.Log("Restarting...");
    }

    //-- never gets hit
    system("pause");
}
