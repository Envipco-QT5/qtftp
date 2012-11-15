;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
;; All rights reserved.
;; Contact: http://www.qt-project.org/legal
;;
;; This file is part of the tools applications of the Qt Toolkit.
;;
;; $QT_BEGIN_LICENSE:LGPL$
;; Commercial License Usage
;; Licensees holding valid commercial Qt licenses may use this file in
;; accordance with the commercial license agreement provided with the
;; Software or, alternatively, in accordance with the terms contained in
;; a written agreement between you and Digia.  For licensing terms and
;; conditions see http://qt.digia.com/licensing.  For further information
;; use the contact form at http://qt.digia.com/contact-us.
;;
;; GNU Lesser General Public License Usage
;; Alternatively, this file may be used under the terms of the GNU Lesser
;; General Public License version 2.1 as published by the Free Software
;; Foundation and appearing in the file LICENSE.LGPL included in the
;; packaging of this file.  Please review the following information to
;; ensure the GNU Lesser General Public License version 2.1 requirements
;; will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
;;
;; In addition, as a special exception, Digia gives you certain additional
;; rights.  These rights are described in the Digia Qt LGPL Exception
;; version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
;;
;; GNU General Public License Usage
;; Alternatively, this file may be used under the terms of the GNU
;; General Public License version 3.0 as published by the Free Software
;; Foundation and appearing in the file LICENSE.GPL included in the
;; packaging of this file.  Please review the following information to
;; ensure the GNU General Public License version 3.0 requirements will be
;; met: http://www.gnu.org/copyleft/gpl.html.
;;
;;
;; $QT_END_LICENSE$
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Script generated by the HM NIS Edit Script Wizard.

!include "config.nsh"
!include "includes\global.nsh"

!define PRODUCT_PUBLISHER "Digia Plc and/or its subsidiary(-ies)"
!define PRODUCT_WEB_SITE "http://qt.nokia.com"

!define INSTALL_ICON "images\install.ico"
!define WELCOME_PAGE_ICON "images\qt-wizard.bmp"
!define PAGE_HEADER_ICON "images\qt-header.bmp"

!include "MUI.nsh"

; modules
!include "modules\mingw.nsh"
!include "modules\opensource.nsh"
!include "includes\instdir.nsh"
!include "modules\environment.nsh"
!include "modules\registeruiext.nsh"
!ifndef OPENSOURCE_BUILD
!include "modules\msvc.nsh"
!include "modules\addin7x.nsh"
!include "modules\qsa.nsh"
!include "modules\addin60.nsh"
!include "modules\debugext.nsh"
!include "modules\license.nsh"
!include "modules\vsip.nsh"
!include "modules\help.nsh"
!include "modules\evaluation.nsh"
!include "modules\eclipse.nsh"
!include "modules\qtjambieclipse.nsh"
!endif

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${INSTALL_ICON}"
!define MUI_UNICON "${INSTALL_ICON}"

!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "${PAGE_HEADER_ICON}"
!define MUI_HEADERIMAGE_UNBITMAP "${PAGE_HEADER_ICON}"

!define MUI_WELCOMEFINISHPAGE_BITMAP "${WELCOME_PAGE_ICON}"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "${WELCOME_PAGE_ICON}"

!ifdef WELCOME_NOTE
  !define MUI_WELCOMEPAGE_TEXT "${WELCOME_NOTE}"
!endif
!insertmacro MUI_PAGE_WELCOME
!insertmacro OPENSOURCE_INITIALIZE
!ifndef OPENSOURCE_BUILD
!insertmacro EVALUATION_INITIALIZE
!insertmacro LICENSECHECK_INITIALIZE
!insertmacro MSVC_INITIALIZE
!insertmacro ADDIN7X_INITIALIZE
!insertmacro ADDIN60_INITIALIZE
!insertmacro DEBUGEXT_INITIALIZE
!insertmacro HELP_INITIALIZE
!insertmacro VSIP_INITIALIZE
!endif
 
!ifdef USE_COMPONENT_PAGE
  !insertmacro MUI_PAGE_COMPONENTS
!endif

!ifdef USE_DIRECTORY_PAGE
  !insertmacro INSTDIR_INITIALIZE
!endif

!ifdef USE_STARTMENU_PAGE
  !define MUI_STARTMENUPAGE_NODISABLE
  !define MUI_STARTMENUPAGE_DEFAULTFOLDER "${DEFAULT_STARTMENU_STRING}"
  !insertmacro MUI_PAGE_STARTMENU 1 $STARTMENU_STRING
!endif

!insertmacro MINGW_INITIALIZE
!insertmacro ENVIRONMENT_INITIALIZE
!insertmacro REGISTERUIEXT_INITIALIZE
!ifndef OPENSOURCE_BUILD
!insertmacro QSA_INITIALIZE
!insertmacro ECLIPSE_INITIALIZE
!insertmacro QTJAMBIECLIPSE_INITIALIZE
!endif
 
!define MUI_FINISHPAGE_NOAUTOCLOSE

!insertmacro MUI_PAGE_INSTFILES
!ifdef README_FILE
  !define MUI_FINISHPAGE_SHOWREADME ${README_FILE}
!else
  !ifdef README_FUNCTION
    !define MUI_FINISHPAGE_SHOWREADME
    !define MUI_FINISHPAGE_SHOWREADME_TEXT "${README_FUNCTION}"
    !define MUI_FINISHPAGE_SHOWREADME_FUNCTION "CommonReadmeFunction"
  !endif
!endif
!ifdef RUN_FUNCTION
  !define MUI_FINISHPAGE_RUN
  !define MUI_FINISHPAGE_RUN_TEXT "${RUN_FUNCTION}"
  !define MUI_FINISHPAGE_RUN_FUNCTION "CommonRunFunction"
!endif
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!define UNINSTALLER_CONFIRM_PAGE "confirmpage.ini"
UninstPage custom un.UninstallerConfirmPage
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile ${OUTPUT_FILE}

Section -PreCommonSection
!ifdef INSTDIR_0 ;the default one, must exist
  strcpy $INSTDIR $${INSTDIR_0}_INSTDIR
  ${StrRep} $PRODUCT_UNIQUE_KEY "${PRODUCT_NAME} ${PRODUCT_VERSION} - $INSTDIR" "\" "_"
  strcpy $PRODUCT_UNIQUE_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\$PRODUCT_UNIQUE_KEY"
  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_0}_INSTDIR" "$${INSTDIR_0}_INSTDIR"
!endif
!ifdef INSTDIR_1
  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_1}_INSTDIR" "$${INSTDIR_1}_INSTDIR"
!endif
!ifdef INSTDIR_2
  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_2}_INSTDIR" "$${INSTDIR_2}_INSTDIR"
!endif
!ifdef INSTDIR_3
  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_3}_INSTDIR" "$${INSTDIR_3}_INSTDIR"
!endif
!ifdef INSTDIR_4
  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_4}_INSTDIR" "$${INSTDIR_4}_INSTDIR"
!endif
!ifdef INSTDIR_5
  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_5}_INSTDIR" "$${INSTDIR_5}_INSTDIR"
!endif

  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "StartMenu" "$STARTMENU_STRING"
  CreateDirectory "$SMPROGRAMS\$STARTMENU_STRING"
SectionEnd

!insertmacro OPENSOURCE_SECTIONS
!insertmacro MINGW_SECTIONS
!insertmacro ENVIRONMENT_SECTIONS
!insertmacro REGISTERUIEXT_SECTIONS
!ifndef OPENSOURCE_BUILD
!insertmacro MSVC_SECTIONS
!insertmacro ADDIN7X_SECTIONS
!insertmacro ADDIN60_SECTIONS
!insertmacro VSIP_SECTIONS
!insertmacro HELP_SECTIONS
!insertmacro DEBUGEXT_SECTIONS
!insertmacro LICENSECHECK_SECTIONS
!insertmacro QSA_SECTIONS
!insertmacro EVALUATION_SECTIONS
!insertmacro ECLIPSE_SECTIONS
!insertmacro QTJAMBIECLIPSE_SECTIONS
!endif

!insertmacro INSTDIR_FUNCTIONS

Section -CommonSection
  WriteUninstaller "$INSTDIR\uninst.exe"

  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "DisplayName" "$(^Name)"
  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr SHCTX "$PRODUCT_UNIQUE_KEY" "Publisher" "${PRODUCT_PUBLISHER}"

  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\$STARTMENU_STRING\qt.nokia.com.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\$STARTMENU_STRING\Uninstall ${PRODUCT_NAME} ${PRODUCT_VERSION}.lnk" "$INSTDIR\uninst.exe"
  SetOutPath "$INSTDIR"
SectionEnd

Function CheckLocalLicenseProduct
!ifdef MODULE_LICENSECHECK
  !insertmacro QSA_CHECKLICENSEPRODUCT
!endif
FunctionEnd

Function .onInit
  StrCpy $STARTMENU_STRING "${DEFAULT_STARTMENU_STRING}"

!ifdef USE_UNINSTALL_PREVIOUS
  push "${PRODUCT_NAME}"
  call GetExistsPreviousInstallationOfProduct
  exch $0
  StrCmp $0 true 0 +3
    MessageBox MB_OK|MB_ICONSTOP "A previous installation of ${PRODUCT_NAME} was detected.$\nPlease uninstall it before running this installer."
    Abort
  pop $0
!endif

  call SetAdminVar
  StrCmp "$RUNNING_AS_ADMIN" "false" 0 common_running_as_admin
!ifdef USE_ADMIN_CHECK
    MessageBox MB_OK|MB_ICONSTOP "You need to have administrator rights to install this software!"
    Abort
!endif
    SetShellVarContext current
    goto common_admin_check_done
  common_running_as_admin:
    SetShellVarContext all
  common_admin_check_done:

  !insertmacro INSTDIR_STARTUP

  !insertmacro OPENSOURCE_STARTUP
  !insertmacro ENVIRONMENT_STARTUP
  !insertmacro REGISTERUIEXT_STARTUP
  !insertmacro MINGW_STARTUP
!ifndef OPENSOURCE_BUILD
  !insertmacro LICENSECHECK_STARTUP
  !insertmacro MSVC_STARTUP
  !insertmacro EVALUATION_STARTUP
  !insertmacro ADDIN7X_STARTUP
  !insertmacro ADDIN60_STARTUP
  !insertmacro DEBUGEXT_STARTUP
  !insertmacro VSIP_STARTUP
  !insertmacro HELP_STARTUP
  !insertmacro QSA_STARTUP
  !insertmacro ECLIPSE_STARTUP
  !insertmacro QTJAMBIECLIPSE_STARTUP
!endif
FunctionEnd

Function .onInstSuccess
  !insertmacro ENVIRONMENT_FINISH
  !insertmacro REGISTERUIEXT_FINISH
  !insertmacro OPENSOURCE_FINISH
  !insertmacro MINGW_FINISH
!ifndef OPENSOURCE_BUILD
  !insertmacro LICENSECHECK_FINISH
  !insertmacro MSVC_FINISH
  !insertmacro EVALUATION_FINISH
  !insertmacro ADDIN7X_FINISH
  !insertmacro ADDIN60_FINISH
  !insertmacro DEBUGEXT_FINISH
  !insertmacro VSIP_FINISH
  !insertmacro HELP_FINISH
  !insertmacro QSA_FINISH
  !insertmacro ECLIPSE_FINISH
  !insertmacro QTJAMBIECLIPSE_FINISH
!endif
FunctionEnd

Function un.onUninstSuccess
  !insertmacro ENVIRONMENT_UNFINISH
  !insertmacro REGISTERUIEXT_UNFINISH
  !insertmacro OPENSOURCE_UNFINISH
  !insertmacro MINGW_UNFINISH
!ifndef OPENSOURCE_BUILD
  !insertmacro LICENSECHECK_UNFINISH
  !insertmacro MSVC_UNFINISH
  !insertmacro EVALUATION_UNFINISH
  !insertmacro ADDIN7X_UNFINISH
  !insertmacro ADDIN60_UNFINISH
  !insertmacro DEBUGEXT_UNFINISH
  !insertmacro VSIP_UNFINISH
  !insertmacro HELP_UNFINISH
  !insertmacro QSA_UNFINISH
  !insertmacro ECLIPSE_UNFINISH
  !insertmacro QTJAMBIECLIPSE_UNFINISH
!endif
FunctionEnd

Function un.onInit
  call un.SetAdminVar
  StrCmp "$RUNNING_AS_ADMIN" "false" 0 common_running_as_admin
!ifdef USE_ADMIN_CHECK
    MessageBox MB_OK|MB_ICONSTOP "You do not have the required access rights to uninstall this package."
    Abort
!endif
    SetShellVarContext current
    goto common_admin_check_done
  common_running_as_admin:
    SetShellVarContext all
  common_admin_check_done:

  ${UnStrRep} $PRODUCT_UNIQUE_KEY "${PRODUCT_NAME} ${PRODUCT_VERSION} - $INSTDIR" "\" "_"
  strcpy $PRODUCT_UNIQUE_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\$PRODUCT_UNIQUE_KEY"

  push $0
  ClearErrors
  ReadRegStr $0 SHCTX "$PRODUCT_UNIQUE_KEY" "DisplayName"
  IfErrors 0 +3
    MessageBox MB_OK|MB_ICONSTOP "The uninstaller was unable to find the product to uninstall."
    Abort
  pop $0

  ReadRegStr $STARTMENU_STRING SHCTX "$PRODUCT_UNIQUE_KEY" "StartMenu"
  StrCmp "$STARTMENU_STRING" "" 0 +2
    StrCpy $STARTMENU_STRING "${DEFAULT_STARTMENU_STRING}"

!ifdef INSTDIR_0 ;the default one, must exist
  ReadRegStr $${INSTDIR_0}_INSTDIR SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_0}_INSTDIR"
!endif
!ifdef INSTDIR_1
  ReadRegStr $${INSTDIR_1}_INSTDIR SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_1}_INSTDIR"
!endif
!ifdef INSTDIR_2
  ReadRegStr $${INSTDIR_2}_INSTDIR SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_2}_INSTDIR"
!endif
!ifdef INSTDIR_3
  ReadRegStr $${INSTDIR_3}_INSTDIR SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_3}_INSTDIR"
!endif
!ifdef INSTDIR_4
  ReadRegStr $${INSTDIR_4}_INSTDIR SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_4}_INSTDIR"
!endif
!ifdef INSTDIR_5
  ReadRegStr $${INSTDIR_5}_INSTDIR SHCTX "$PRODUCT_UNIQUE_KEY" "${INSTDIR_5}_INSTDIR"
!endif

  !insertmacro ENVIRONMENT_UNSTARTUP
  !insertmacro REGISTERUIEXT_UNSTARTUP
  !insertmacro OPENSOURCE_UNSTARTUP
  !insertmacro MINGW_UNSTARTUP
!ifndef OPENSOURCE_BUILD
  !insertmacro LICENSECHECK_UNSTARTUP
  !insertmacro MSVC_UNSTARTUP
  !insertmacro EVALUATION_UNSTARTUP
  !insertmacro ADDIN7X_UNSTARTUP
  !insertmacro ADDIN60_UNSTARTUP
  !insertmacro DEBUGEXT_UNSTARTUP
  !insertmacro VSIP_UNSTARTUP
  !insertmacro HELP_UNSTARTUP
  !insertmacro QSA_UNSTARTUP
  !insertmacro ECLIPSE_UNSTARTUP
  !insertmacro QTJAMBIECLIPSE_UNSTARTUP
!endif
  
  !insertmacro MUI_INSTALLOPTIONS_EXTRACT "${UNINSTALLER_CONFIRM_PAGE}"
FunctionEnd

!insertmacro OPENSOURCE_UNINSTALL
!insertmacro ENVIRONMENT_UNINSTALL
!insertmacro REGISTERUIEXT_UNINSTALL
!insertmacro MINGW_UNINSTALL
!ifndef OPENSOURCE_BUILD
!insertmacro HELP_UNINSTALL
!insertmacro DEBUGEXT_UNINSTALL
!insertmacro MSVC_UNINSTALL
!insertmacro EVALUATION_UNINSTALL
!insertmacro QSA_UNINSTALL
!insertmacro ECLIPSE_UNINSTALL
!insertmacro QTJAMBIECLIPSE_UNINSTALL
!endif

Section Uninstall
  !ifndef OPENSOURCE_BUILD
  !insertmacro LICENSECHECK_UNINSTALL
  !insertmacro ADDIN7X_UNINSTALL
  !insertmacro ADDIN60_UNINSTALL
  !insertmacro VSIP_UNINSTALL
  !endif

  ; COMMON
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$SMPROGRAMS\$STARTMENU_STRING\Uninstall ${PRODUCT_NAME} ${PRODUCT_VERSION}.lnk"
  Delete "$SMPROGRAMS\$STARTMENU_STRING\qt.nokia.com.lnk"

  RMDir "$SMPROGRAMS\$STARTMENU_STRING"
  RMDir "$INSTDIR"
  
  DeleteRegKey SHCTX "$PRODUCT_UNIQUE_KEY"
SectionEnd

Function CommonRunFunction
  !ifndef OPENSOURCE_BUILD
  !insertmacro MSVC_RUN_FUNCTION
  !insertmacro QSA_RUN_FUNCTION
  !endif
  !insertmacro MINGW_RUN_FUNCTION
  DoneRunFunction:
FunctionEnd

Function CommonReadmeFunction
  !ifndef OPENSOURCE_BUILD
  !insertmacro MSVC_README_FUNCTION
  !endif
  !insertmacro MINGW_README_FUNCTION
  DoneReadmeFunction:
FunctionEnd

Function un.UninstallerConfirmPage
  !insertmacro MUI_HEADER_TEXT "Confirm" "Confirm Uninstallation Directories"
  !insertmacro MUI_INSTALLOPTIONS_WRITE "${UNINSTALLER_CONFIRM_PAGE}" "Field 2" "Text" "$UninstallerConfirmProduct"
  !insertmacro MUI_INSTALLOPTIONS_DISPLAY "${UNINSTALLER_CONFIRM_PAGE}"
FunctionEnd

;pops product name from stack and as result pushes TRUE or FALSE on stack
Function GetExistsPreviousInstallationOfProduct
  exch $0
  push $1
  push $2
  push $3

  StrCpy $1 0
  loop:
    EnumRegKey $2 HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall $1
    StrCmp $2 "" no_reg_key_found
    ${StrStr} $3 $2 $0
    StrCmp $3 $2 reg_key_found
    IntOp $1 $1 + 1
    goto loop
  
  reg_key_found:
  push true
  goto done
  
  no_reg_key_found:
  push false
  
  done:
  exch
  pop $3
  exch
  pop $2
  exch
  pop $1
  exch
  pop $0
FunctionEnd

;pops product name from stack
Function WarnIfInstalledProductDetected
  exch $0
  push $0
  call GetExistsPreviousInstallationOfProduct
  exch $1
  StrCmp $1 true +1 +3
    MessageBox MB_YESNO|MB_ICONQUESTION "An existing installation of $0 was detected.$\nIt is recommended to deinstall $0 before continuing.$\nDo you want to continue this installation nevertheless?" IDYES +2 IDNO +1
      Abort
  pop $1
  pop $0
FunctionEnd

;sets $RUNNING_AS_ADMIN to "true" if Admin or Power user
!macro SetAdminVar UN
Function ${UN}SetAdminVar
  push $0
  ClearErrors
  UserInfo::GetAccountType
  IfErrors Admin ;It's probably Win95
  pop $0
  StrCmp $0 "Admin" Admin
  StrCmp $0 "Power" Admin

  StrCpy $RUNNING_AS_ADMIN "false"
  goto Done

  Admin:
  StrCpy $RUNNING_AS_ADMIN "true"

  Done:
  pop $0
FunctionEnd
!macroend
!insertmacro SetAdminVar ""
!insertmacro SetAdminVar "un."

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro OPENSOURCE_DESCRIPTION
  !insertmacro ENVIRONMENT_DESCRIPTION
  !insertmacro REGISTERUIEXT_DESCRIPTION
  !insertmacro MINGW_DESCRIPTION
  !ifndef OPENSOURCE_BUILD
  !insertmacro MSVC_DESCRIPTION
  !insertmacro EVALUATION_DESCRIPTION
  !insertmacro ADDIN7X_DESCRIPTION
  !insertmacro ADDIN60_DESCRIPTION
  !insertmacro DEBUGEXT_DESCRIPTION
  !insertmacro HELP_DESCRIPTION
  !insertmacro VSIP_DESCRIPTION
  !insertmacro QSA_DESCRIPTION
  !insertmacro ECLIPSE_DESCRIPTION
  !insertmacro QTJAMBIECLIPSE_DESCRIPTION
  !endif
!insertmacro MUI_FUNCTION_DESCRIPTION_END
