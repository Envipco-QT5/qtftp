TEMPLATE = subdirs

# Directories
!wince*:SUBDIRS += \
           headers

SUBDIRS += bic \
           collections \
           compile \
           compilerwarnings \
           exceptionsafety \
           macgui \
           macplist \
	   mediaobject \
#	   mediaobject_wince_ds9 \   This is Windows CE only (we test the second phonon backend ds9 here)
           moc \
           modeltest \
           q3accel \
           q3action \
           q3actiongroup \
           q3buttongroup \
           q3canvas \
           q3checklistitem \
           q3cstring \
           q3databrowser \
           q3dateedit \
           q3datetimeedit \
           q3deepcopy \
           q3dict \
           q3dns \
           q3dockwindow \
           q3filedialog \
           q3groupbox \
           q3hbox \
           q3header \
           q3iconview \
           q3listview \
           q3listviewitemiterator \
           q3mainwindow \
           q3popupmenu \
           q3process \
           q3progressbar \
           q3progressdialog \
           q3ptrlist \
           q3richtext \
           q3scrollview \
           q3semaphore \
           q3serversocket \
           q3socket \
           q3socketdevice \
           q3sqlcursor \
           q3sqlselectcursor \
           q3stylesheet \
           q3tabdialog \
           q3table \
           q3textbrowser \
           q3textedit \
           q3textstream \
           q3timeedit \
           q3toolbar \
           q3urloperator \
           q3valuelist \
           q3valuevector \
           qabstractbutton \
           qabstractitemmodel \
           qabstractitemview \
           qabstractprintdialog \
           qabstractscrollarea \
           qabstractslider \
           qabstractsocket \
           qabstractspinbox \
           qabstracttextdocumentlayout \
           qaccessibility \
           qaccessibility_mac \
           qaction \
           qactiongroup \
           qalgorithms \
           qapplication \
           qatomicint \
           qatomicpointer \
           qbitarray \
           qboxlayout \
           qbrush \
           qbuffer \
           qbuttongroup \
           qbytearray \
           qcache \
           qchar \
           qcheckbox \
           qclipboard \
           qcolor \
           qcolordialog \
           qcombobox \
           qcompleter \
           qcomplextext \
           qcopchannel \
           qcoreapplication \
           qcryptographichash \
           qcssparser \
           qdatastream \
           qdatawidgetmapper \
           qdate \
           qdatetime \
           qdatetimeedit \
	   qdbuspendingcall \
	   qdbuspendingreply \
           qdebug \
           qdesktopservices \
           qdesktopwidget \
           qdial \
           qdialog \
           qdialogbuttonbox \
           qdir \
           qdirectpainter \
           qdirmodel \
           qdockwidget \
           qdom \
           qdoublespinbox \
           qdoublevalidator \
           qdrag \
           qerrormessage \
           qeventloop \
           qexplicitlyshareddatapointer \
           qfile \
           qfiledialog \
           qfileinfo \
           qfilesystemwatcher \
           qfilesystemmodel \
           qflags \
           qfocusevent \
           qfocusframe \
           qfont \
           qfontdatabase \
           qfontdialog \
           qfontmetrics \
           qftp \
           qgetputenv \
           qgl \
           qglobal \
           qgraphicsitem \
           qgraphicsitemanimation \
           qgraphicsscene \
           qgraphicsview \
           qgridlayout \
           qgroupbox \
           qguivariant \
           qhash \
           qheaderview \
           qhelpcontentmodel \
           qhelpenginecore \
           qhelpgenerator \
           qhelpindexmodel \
           qhelpprojectdata \
           qhostaddress \
           qhostinfo \
           qhttp \
	   qhttpnetworkreply \
	   qhttpnetworkconnection \
           qicon \
           qicoimageformat \
           qimage \
           qimageiohandler \
           qimagereader \
           qimagewriter \
           qinputdialog \
           qintvalidator \
           qiodevice \
           qitemdelegate \
           qitemeditorfactory \
           qitemmodel \
           qitemselectionmodel \
           qitemview \
           qkeyevent \
           qkeysequence \
           qlabel \
           qlayout \
           qlcdnumber \
           qlibrary \
           qline \
           qlineedit \
           qlist \           
           q3listbox \
           qlistview \
           qlistwidget \
           qlocale \
           qmainwindow \
           qmake \
           qmap \
           qmdiarea \
           qmdisubwindow \
           qmenu \
           qmenubar \
           qmessagebox \
           qmetaobject \
           qmetatype \
           qmouseevent \
           qmouseevent_modal \
           qmovie \
           qmultiscreen \
           qmutex \
           qmutexlocker \
           qnativesocketengine \
	   qnetworkcookie \
	   qnetworkcookiejar \
           qnetworkinterface \
           qnetworkproxy \
	   qnetworkrequest \
	   qnetworkreply \
           qnumeric \
           qobject \
           qobjectrace \
           qpaintengine \
           qpainter \
           qpainterpath \
           qpalette \
           qpathclipper \
           qpen \
           qpicture \
           qpixmap \
           qpixmapcache \
           qpixmapfilter \
           qplaintextedit \
           qpoint \
           qpointarray \
           qpointer \
           qprinter \
           qprinterinfo \
           qprocess \
           qprogressbar \
           qprogressdialog \
           qpushbutton \
           qqueue \
           qradiobutton \
           qreadlocker \
           qreadwritelock \
           qrect \
           qregexp \
           qregexpvalidator \
           qregion \
           qresourceengine \
           qscriptable \
           qscriptclass \
           qscriptcontext \
           qscriptcontextinfo \
           qscriptengine \
           qscriptengineagent \
           qscriptjstestsuite \
           qscriptv8testsuite \
           qscriptqobject \
           qscriptstring \
           qscriptvalue \
           qscriptvalueiterator \
           qscriptenginedebugger \
           qscrollarea \
           qsemaphore \
	   qsharedpointer \
           qset \
           qsettings \
           qshortcut \
           qsignalmapper \
           qsignalspy \
           qsize \
           qsizef \
           qslider \
           qsocketnotifier \
           qsocks5socketengine \
           qsortfilterproxymodel \
           qsound \
           qspinbox \
           qsplitter \
           qsql \
           qsqldatabase \
           qsqlerror \
           qsqlfield \
           qsqlquery \
           qsqlquerymodel \
           qsqlrecord \
           qsqlrelationaltablemodel \
           qsqltablemodel \
           qsqlthread \
           qsslcertificate \
           qsslcipher \
           qsslerror \
           qsslkey \
           qsslsocket \
           qstackedlayout \
           qstackedwidget \
           qstandarditem \
           qstandarditemmodel \
           qstatusbar \
           qstl \
           qstring \
           qstringmatcher \
           qstringlist \
           qstringlistmodel \
           qstyle \
           qstyleoption \
           qstylesheetstyle \
           qsvgdevice \
           qsvggenerator \
           qsvgrenderer \
           qsyntaxhighlighter \
           qsystemtrayicon \
           qtabbar \
           qtableview \
           qtablewidget \
           qtabwidget \
           qtcpserver \
           qtcpsocket \
           qtemporaryfile \
           qtessellator \
           qtextblock \
           qtextboundaryfinder \
           qtextbrowser \
           qtextcodec \
           qtextcursor \
           qtextdocument \
           qtextdocumentfragment \
           qtextdocumentlayout \
           qtextedit \
           qtextformat \
           qtextlayout \
           qtextlist \
           qtextobject \
           qtextpiecetable \
           qtextscriptengine \
           qtextstream \
           qtexttable \
           qthread \
	   qthreadonce \
           qthreadstorage \
           qtime \
           qtimeline \
           qtimer \
           qtmd5 \
           qtoolbar \
           qtoolbox \
           qtoolbutton \
           qtooltip \
           qtranslator \
           qtransform \
           qtransformedscreen \
           qtreeview \
           qtreewidget \
           qtreewidgetitemiterator \
           qtwidgets \
           qudpsocket \
           qundogroup \
           qundostack \
           qurl \
           quuid \
           qvariant \
           qvarlengtharray \
           qvector \
           qwaitcondition \
           qwidget \
           qwidgetaction \
           qwindowsurface \
           qwineventnotifier \
           qwizard \
           qwmatrix \
           qworkspace \
           qwritelocker \
           qwsembedwidget \
           qwsinputmethod \
           qwswindowsystem \
           qx11info \
           qxml \
           qxmlinputsource \
           qxmlsimplereader \
           qxmlstream \
           selftests \
           symbols \
           qrand \
           uic \
           uic3

contains(QT_CONFIG, OdfWriter):SUBDIRS += qzip qtextodfwriter

# Enable the tests specific to QtXmlPatterns. If you add a test, remember to
# update runQtXmlPatternsTests.sh too. Remember that this file, auto.pro, is
# not respected by some test system, they just have a script which loop over
# the folders.
contains(QT_CONFIG, xmlpatterns) {
SUBDIRS += checkxmlfiles                \
           patternistexamplefiletree    \
           patternistexamples           \
           patternistheaders            \
           qabstractmessagehandler      \
           qabstracturiresolver         \
           qabstractxmlforwarditerator  \
           qabstractxmlnodemodel        \
           qabstractxmlreceiver         \
           qapplicationargumentparser   \
           qautoptr                     \
           qsimplexmlnodemodel          \
           qsourcelocation              \
           qxmlformatter                \
           qxmlitem                     \
           qxmlname                     \
           qxmlnamepool                 \
           qxmlnodemodelindex           \
           qxmlquery                    \
           qxmlresultitems              \
           qxmlserializer               \
           xmlpatterns                  \
           xmlpatternsdiagnosticsts     \
           xmlpatternsview              \
           xmlpatternsxqts              \
           xmlpatternsxslts

xmlpatternsdiagnosticsts.depends = xmlpatternsxqts
xmlpatternsview.depends = xmlpatternsxqts
xmlpatternsxslts.depends = xmlpatternsxqts
}

unix:!embedded:contains(QT_CONFIG, dbus):SUBDIRS += \
           qdbusabstractadaptor \
           qdbusconnection \
           qdbusinterface \
           qdbuslocalcalls \
           qdbusmarshall \
           qdbusmetaobject \
           qdbusmetatype \
	   qdbusperformance \
           qdbusreply \
           qdbusthreading \
           qdbusxmlparser

contains(QT_CONFIG, webkit): SUBDIRS += \
           qwebframe \
           qwebpage

