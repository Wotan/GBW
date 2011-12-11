#include <iostream>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include "App.hpp"
#include "Settings.hpp"


InputWindow::InputWindow(App *app, QWidget *parent) :
  QDialog(parent),
  mApp(app)
{
  setWindowFlags(Qt::Window);
  setWindowTitle(QString("Input"));
}

void	InputWindow::InitWidget()
{
  Qt::Key *keyTab = mApp->GetMainWindow()->GetKeyTab();
  KeyEdit *curKeyEdit;

  int cKey = 0;
  mMainLayout = new QGridLayout(this);
  for (int i = 0; i < 8; i++)
    {
      curKeyEdit = new KeyEdit(cKey, mApp, this);
      curKeyEdit->setText(
      InputWindow::GetKeyString((Qt::Key)keyTab[cKey]).c_str());
      mMainLayout->addWidget(curKeyEdit, cKey, 1);

      curKeyEdit = new KeyEdit(cKey + 8, mApp, this);
      mMainLayout->addWidget(curKeyEdit, cKey, 2);

      cKey++;
    }
  mTabLabel[0] = new QLabel(QString("Up"), this);
  mTabLabel[1] = new QLabel(QString("Down"), this);
  mTabLabel[2] = new QLabel(QString("Right"), this);
  mTabLabel[3] = new QLabel(QString("Left"), this);
  mTabLabel[4] = new QLabel(QString("A"), this);
  mTabLabel[5] = new QLabel(QString("B"), this);
  mTabLabel[6] = new QLabel(QString("Start"), this);
  mTabLabel[7] = new QLabel(QString("Select"), this);
  for (int i = 0; i < 8; i++)
    mMainLayout->addWidget(mTabLabel[i], i, 0);
  setLayout(mMainLayout);
}

KeyEdit::KeyEdit(int id, App *app, QWidget *parent) :
  QLineEdit(parent),
  mApp(app),
  mId(id)
{
}

void KeyEdit::keyPressEvent(QKeyEvent *keyEvent)
{
  int key = keyEvent->key();

  setText(InputWindow::GetKeyString((Qt::Key)key).c_str());
  if (mId >= 0 && mId < 8)
    {
      Qt::Key *keyTab = mApp->GetMainWindow()->GetKeyTab();
      keyTab[mId] = (Qt::Key)key;
    }
}

std::string InputWindow::GetKeyString(Qt::Key key)
{
  switch (key)
    {
    case Qt::Key_Escape: return "Escape";
    case Qt::Key_Tab: return "Tab";
    case Qt::Key_Backtab: return "Backtab";
    case Qt::Key_Backspace: return "Backspace";
    case Qt::Key_Return: return "Return";
    case Qt::Key_Enter: return "Enter";
    case Qt::Key_Insert: return "Insert";
    case Qt::Key_Delete: return "Delete";
    case Qt::Key_Pause: return "Pause";
    case Qt::Key_Print: return "Print";
    case Qt::Key_SysReq: return "SysReq";
    case Qt::Key_Clear: return "Clear";
    case Qt::Key_Home: return "Home";
    case Qt::Key_End: return "End";
    case Qt::Key_Left: return "Left";
    case Qt::Key_Up: return "Up";
    case Qt::Key_Right: return "Right";
    case Qt::Key_Down: return "Down";
    case Qt::Key_PageUp: return "PageUp";
    case Qt::Key_PageDown: return "PageDown";
    case Qt::Key_Shift: return "Shift";
    case Qt::Key_Control: return "Control";
    case Qt::Key_Meta: return "Meta";
    case Qt::Key_Alt: return "Alt";
    case Qt::Key_AltGr: return "AltGr";
    case Qt::Key_CapsLock: return "CapsLock";
    case Qt::Key_NumLock: return "NumLock";
    case Qt::Key_ScrollLock: return "ScrollLock";
    case Qt::Key_F1: return "F1";
    case Qt::Key_F2: return "F2";
    case Qt::Key_F3: return "F3";
    case Qt::Key_F4: return "F4";
    case Qt::Key_F5: return "F5";
    case Qt::Key_F6: return "F6";
    case Qt::Key_F7: return "F7";
    case Qt::Key_F8: return "F8";
    case Qt::Key_F9: return "F9";
    case Qt::Key_F10: return "F10";
    case Qt::Key_F11: return "F11";
    case Qt::Key_F12: return "F12";
    case Qt::Key_F13: return "F13";
    case Qt::Key_F14: return "F14";
    case Qt::Key_F15: return "F15";
    case Qt::Key_F16: return "F16";
    case Qt::Key_F17: return "F17";
    case Qt::Key_F18: return "F18";
    case Qt::Key_F19: return "F19";
    case Qt::Key_F20: return "F20";
    case Qt::Key_F21: return "F21";
    case Qt::Key_F22: return "F22";
    case Qt::Key_F23: return "F23";
    case Qt::Key_F24: return "F24";
    case Qt::Key_F25: return "F25";
    case Qt::Key_F26: return "F26";
    case Qt::Key_F27: return "F27";
    case Qt::Key_F28: return "F28";
    case Qt::Key_F29: return "F29";
    case Qt::Key_F30: return "F30";
    case Qt::Key_F31: return "F31";
    case Qt::Key_F32: return "F32";
    case Qt::Key_F33: return "F33";
    case Qt::Key_F34: return "F34";
    case Qt::Key_F35: return "F35";
    case Qt::Key_Super_L: return "Super_L";
    case Qt::Key_Super_R: return "Super_R";
    case Qt::Key_Menu: return "Menu";
    case Qt::Key_Hyper_L: return "Hyper_L";
    case Qt::Key_Hyper_R: return "Hyper_R";
    case Qt::Key_Help: return "Help";
    case Qt::Key_Direction_L: return "Direction_L";
    case Qt::Key_Direction_R: return "Direction_R";
    case Qt::Key_Space: return "Space";
    case Qt::Key_Exclam: return "Exclam";
    case Qt::Key_QuoteDbl: return "QuoteDbl";
    case Qt::Key_NumberSign: return "NumberSign";
    case Qt::Key_Dollar: return "Dollar";
    case Qt::Key_Percent: return "Percent";
    case Qt::Key_Ampersand: return "Ampersand";
    case Qt::Key_Apostrophe: return "Apostrophe";
    case Qt::Key_ParenLeft: return "ParenLeft";
    case Qt::Key_ParenRight: return "ParenRight";
    case Qt::Key_Asterisk: return "Asterisk";
    case Qt::Key_Plus: return "Plus";
    case Qt::Key_Comma: return "Comma";
    case Qt::Key_Minus: return "Minus";
    case Qt::Key_Period: return "Period";
    case Qt::Key_Slash: return "Slash";
    case Qt::Key_0: return "0";
    case Qt::Key_1: return "1";
    case Qt::Key_2: return "2";
    case Qt::Key_3: return "3";
    case Qt::Key_4: return "4";
    case Qt::Key_5: return "5";
    case Qt::Key_6: return "6";
    case Qt::Key_7: return "7";
    case Qt::Key_8: return "8";
    case Qt::Key_9: return "9";
    case Qt::Key_Colon: return "Colon";
    case Qt::Key_Semicolon: return "Semicolon";
    case Qt::Key_Less: return "Less";
    case Qt::Key_Equal: return "Equal";
    case Qt::Key_Greater: return "Greater";
    case Qt::Key_Question: return "Question";
    case Qt::Key_At: return "At";
    case Qt::Key_A: return "A";
    case Qt::Key_B: return "B";
    case Qt::Key_C: return "C";
    case Qt::Key_D: return "D";
    case Qt::Key_E: return "E";
    case Qt::Key_F: return "F";
    case Qt::Key_G: return "G";
    case Qt::Key_H: return "H";
    case Qt::Key_I: return "I";
    case Qt::Key_J: return "J";
    case Qt::Key_K: return "K";
    case Qt::Key_L: return "L";
    case Qt::Key_M: return "M";
    case Qt::Key_N: return "N";
    case Qt::Key_O: return "O";
    case Qt::Key_P: return "P";
    case Qt::Key_Q: return "Q";
    case Qt::Key_R: return "R";
    case Qt::Key_S: return "S";
    case Qt::Key_T: return "T";
    case Qt::Key_U: return "U";
    case Qt::Key_V: return "V";
    case Qt::Key_W: return "W";
    case Qt::Key_X: return "X";
    case Qt::Key_Y: return "Y";
    case Qt::Key_Z: return "Z";
    case Qt::Key_BracketLeft: return "BracketLeft";
    case Qt::Key_Backslash: return "Backslash";
    case Qt::Key_BracketRight: return "BracketRight";
    case Qt::Key_AsciiCircum: return "AsciiCircum";
    case Qt::Key_Underscore: return "Underscore";
    case Qt::Key_QuoteLeft: return "QuoteLeft";
    case Qt::Key_BraceLeft: return "BraceLeft";
    case Qt::Key_Bar: return "Bar";
    case Qt::Key_BraceRight: return "BraceRight";
    case Qt::Key_AsciiTilde: return "AsciiTilde";
    case Qt::Key_nobreakspace: return "nobreakspace";
    case Qt::Key_exclamdown: return "exclamdown";
    case Qt::Key_cent: return "cent";
    case Qt::Key_sterling: return "sterling";
    case Qt::Key_currency: return "currency";
    case Qt::Key_yen: return "yen";
    case Qt::Key_brokenbar: return "brokenbar";
    case Qt::Key_section: return "section";
    case Qt::Key_diaeresis: return "diaeresis";
    case Qt::Key_copyright: return "copyright";
    case Qt::Key_ordfeminine: return "ordfeminine";
    case Qt::Key_guillemotleft: return "guillemotleft";
    case Qt::Key_notsign: return "notsign";
    case Qt::Key_hyphen: return "hyphen";
    case Qt::Key_registered: return "registered";
    case Qt::Key_macron: return "macron";
    case Qt::Key_degree: return "degree";
    case Qt::Key_plusminus: return "plusminus";
    case Qt::Key_twosuperior: return "twosuperior";
    case Qt::Key_threesuperior: return "threesuperior";
    case Qt::Key_acute: return "acute";
    case Qt::Key_mu: return "mu";
    case Qt::Key_paragraph: return "paragraph";
    case Qt::Key_periodcentered: return "periodcentered";
    case Qt::Key_cedilla: return "cedilla";
    case Qt::Key_onesuperior: return "onesuperior";
    case Qt::Key_masculine: return "masculine";
    case Qt::Key_guillemotright: return "guillemotright";
    case Qt::Key_onequarter: return "onequarter";
    case Qt::Key_onehalf: return "onehalf";
    case Qt::Key_threequarters: return "threequarters";
    case Qt::Key_questiondown: return "questiondown";
    case Qt::Key_Agrave: return "Agrave";
    case Qt::Key_Aacute: return "Aacute";
    case Qt::Key_Acircumflex: return "Acircumflex";
    case Qt::Key_Atilde: return "Atilde";
    case Qt::Key_Adiaeresis: return "Adiaeresis";
    case Qt::Key_Aring: return "Aring";
    case Qt::Key_AE: return "AE";
    case Qt::Key_Ccedilla: return "Ccedilla";
    case Qt::Key_Egrave: return "Egrave";
    case Qt::Key_Eacute: return "Eacute";
    case Qt::Key_Ecircumflex: return "Ecircumflex";
    case Qt::Key_Ediaeresis: return "Ediaeresis";
    case Qt::Key_Igrave: return "Igrave";
    case Qt::Key_Iacute: return "Iacute";
    case Qt::Key_Icircumflex: return "Icircumflex";
    case Qt::Key_Idiaeresis: return "Idiaeresis";
    case Qt::Key_ETH: return "ETH";
    case Qt::Key_Ntilde: return "Ntilde";
    case Qt::Key_Ograve: return "Ograve";
    case Qt::Key_Oacute: return "Oacute";
    case Qt::Key_Ocircumflex: return "Ocircumflex";
    case Qt::Key_Otilde: return "Otilde";
    case Qt::Key_Odiaeresis: return "Odiaeresis";
    case Qt::Key_multiply: return "multiply";
    case Qt::Key_Ooblique: return "Ooblique";
    case Qt::Key_Ugrave: return "Ugrave";
    case Qt::Key_Uacute: return "Uacute";
    case Qt::Key_Ucircumflex: return "Ucircumflex";
    case Qt::Key_Udiaeresis: return "Udiaeresis";
    case Qt::Key_Yacute: return "Yacute";
    case Qt::Key_THORN: return "THORN";
    case Qt::Key_ssharp: return "ssharp";
    case Qt::Key_division: return "division";
    case Qt::Key_ydiaeresis: return "ydiaeresis";
    case Qt::Key_Multi_key: return "Multi_key";
    case Qt::Key_Codeinput: return "Codeinput";
    case Qt::Key_SingleCandidate: return "SingleCandidate";
    case Qt::Key_MultipleCandidate: return "MultipleCandidate";
    case Qt::Key_PreviousCandidate: return "PreviousCandidate";
    case Qt::Key_Mode_switch: return "Mode_switch";
    case Qt::Key_Kanji: return "Kanji";
    case Qt::Key_Muhenkan: return "Muhenkan";
    case Qt::Key_Henkan: return "Henkan";
    case Qt::Key_Romaji: return "Romaji";
    case Qt::Key_Hiragana: return "Hiragana";
    case Qt::Key_Katakana: return "Katakana";
    case Qt::Key_Hiragana_Katakana: return "Hiragana_Katakana";
    case Qt::Key_Zenkaku: return "Zenkaku";
    case Qt::Key_Hankaku: return "Hankaku";
    case Qt::Key_Zenkaku_Hankaku: return "Zenkaku_Hankaku";
    case Qt::Key_Touroku: return "Touroku";
    case Qt::Key_Massyo: return "Massyo";
    case Qt::Key_Kana_Lock: return "Kana_Lock";
    case Qt::Key_Kana_Shift: return "Kana_Shift";
    case Qt::Key_Eisu_Shift: return "Eisu_Shift";
    case Qt::Key_Eisu_toggle: return "Eisu_toggle";
    case Qt::Key_Hangul: return "Hangul";
    case Qt::Key_Hangul_Start: return "Hangul_Start";
    case Qt::Key_Hangul_End: return "Hangul_End";
    case Qt::Key_Hangul_Hanja: return "Hangul_Hanja";
    case Qt::Key_Hangul_Jamo: return "Hangul_Jamo";
    case Qt::Key_Hangul_Romaja: return "Hangul_Romaja";
    case Qt::Key_Hangul_Jeonja: return "Hangul_Jeonja";
    case Qt::Key_Hangul_Banja: return "Hangul_Banja";
    case Qt::Key_Hangul_PreHanja: return "Hangul_PreHanja";
    case Qt::Key_Hangul_PostHanja: return "Hangul_PostHanja";
    case Qt::Key_Hangul_Special: return "Hangul_Special";
    case Qt::Key_Dead_Grave: return "Dead_Grave";
    case Qt::Key_Dead_Acute: return "Dead_Acute";
    case Qt::Key_Dead_Circumflex: return "Dead_Circumflex";
    case Qt::Key_Dead_Tilde: return "Dead_Tilde";
    case Qt::Key_Dead_Macron: return "Dead_Macron";
    case Qt::Key_Dead_Breve: return "Dead_Breve";
    case Qt::Key_Dead_Abovedot: return "Dead_Abovedot";
    case Qt::Key_Dead_Diaeresis: return "Dead_Diaeresis";
    case Qt::Key_Dead_Abovering: return "Dead_Abovering";
    case Qt::Key_Dead_Doubleacute: return "Dead_Doubleacute";
    case Qt::Key_Dead_Caron: return "Dead_Caron";
    case Qt::Key_Dead_Cedilla: return "Dead_Cedilla";
    case Qt::Key_Dead_Ogonek: return "Dead_Ogonek";
    case Qt::Key_Dead_Iota: return "Dead_Iota";
    case Qt::Key_Dead_Voiced_Sound: return "Dead_Voiced_Sound";
    case Qt::Key_Dead_Semivoiced_Sound: return "Dead_Semivoiced_Sound";
    case Qt::Key_Dead_Belowdot: return "Dead_Belowdot";
    case Qt::Key_Dead_Hook: return "Dead_Hook";
    case Qt::Key_Dead_Horn: return "Dead_Horn";
    case Qt::Key_Back: return "Back";
    case Qt::Key_Forward: return "Forward";
    case Qt::Key_Stop: return "Stop";
    case Qt::Key_Refresh: return "Refresh";
    case Qt::Key_VolumeDown: return "VolumeDown";
    case Qt::Key_VolumeMute: return "VolumeMute";
    case Qt::Key_VolumeUp: return "VolumeUp";
    case Qt::Key_BassBoost: return "BassBoost";
    case Qt::Key_BassUp: return "BassUp";
    case Qt::Key_BassDown: return "BassDown";
    case Qt::Key_TrebleUp: return "TrebleUp";
    case Qt::Key_TrebleDown: return "TrebleDown";
    case Qt::Key_MediaPlay: return "MediaPlay";
    case Qt::Key_MediaStop: return "MediaStop";
    case Qt::Key_MediaPrevious: return "MediaPrevious";
    case Qt::Key_MediaNext: return "MediaNext";
    case Qt::Key_MediaRecord: return "MediaRecord";
    case Qt::Key_HomePage: return "HomePage";
    case Qt::Key_Favorites: return "Favorites";
    case Qt::Key_Search: return "Search";
    case Qt::Key_Standby: return "Standby";
    case Qt::Key_OpenUrl: return "OpenUrl";
    case Qt::Key_LaunchMail: return "LaunchMail";
    case Qt::Key_LaunchMedia: return "LaunchMedia";
    case Qt::Key_Launch0: return "Launch0";
    case Qt::Key_Launch1: return "Launch1";
    case Qt::Key_Launch2: return "Launch2";
    case Qt::Key_Launch3: return "Launch3";
    case Qt::Key_Launch4: return "Launch4";
    case Qt::Key_Launch5: return "Launch5";
    case Qt::Key_Launch6: return "Launch6";
    case Qt::Key_Launch7: return "Launch7";
    case Qt::Key_Launch8: return "Launch8";
    case Qt::Key_Launch9: return "Launch9";
    case Qt::Key_LaunchA: return "LaunchA";
    case Qt::Key_LaunchB: return "LaunchB";
    case Qt::Key_LaunchC: return "LaunchC";
    case Qt::Key_LaunchD: return "LaunchD";
    case Qt::Key_LaunchE: return "LaunchE";
    case Qt::Key_LaunchF: return "LaunchF";
    case Qt::Key_MediaLast: return "MediaLast";
    case Qt::Key_unknown: return "unknown";
    case Qt::Key_Call: return "Call";
    case Qt::Key_Context1: return "Context1";
    case Qt::Key_Context2: return "Context2";
    case Qt::Key_Context3: return "Context3";
    case Qt::Key_Context4: return "Context4";
    case Qt::Key_Flip: return "Flip";
    case Qt::Key_Hangup: return "Hangup";
    case Qt::Key_No: return "No";
    case Qt::Key_Select: return "Select";
    case Qt::Key_Yes: return "Yes";
    case Qt::Key_Execute: return "Execute";
    case Qt::Key_Printer: return "Printer";
    case Qt::Key_Play: return "Play";
    case Qt::Key_Sleep: return "Sleep";
    case Qt::Key_Zoom: return "Zoom";
    case Qt::Key_Cancel: return "Cancel";
    default: return "Unknown Key";
    }
}
