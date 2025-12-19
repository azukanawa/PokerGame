#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
// 播放背景音乐函数
void playBackgroundMusic(const char* music, bool repeat = false,
                         int volume = -1) {
  static int i = 0;
  char cmd[256] = {0};
  sprintf_s(cmd, "open %s alias bgm%d", music, 1);
  MCIERROR ret = mciSendString(cmd, NULL, 0, NULL);
  if (ret != 0) {
    // 获取错误信息
    char err[256] = {0};
    mciGetErrorString(ret, err, sizeof(err));
    printf("[open]:%s", err);
  }
  sprintf_s(cmd, "play bgm%d %s", 1, repeat ? "repeat" : "");
  ret = mciSendString(cmd, NULL, 0, NULL);
  if (ret != 0) {
    // 获取错误信息
    char err[256] = {0};
    mciGetErrorString(ret, err, sizeof(err));
    printf("[play]:%s", err);
  }
  if (volume != -1) {
    sprintf_s(cmd, "setaudio bgm%d volume to %d", 1, volume);
    ret = mciSendString(cmd, NULL, 0, NULL);
    if (ret != 0) {
      // 获取错误信息
      char err[256] = {0};
      mciGetErrorString(ret, err, sizeof(err));
      printf("[set volume]:%s", err);
    }
  }
  i++;
}