#!../expect --
# 03/01/2008 - 1.0 - Limited Release [jhufnage]
# 04/08/2008 - 1.1 - Added versioning information to the title bar [jhufnage]
# 11/16/2009 - 1.2 - Enabled varable resolution [jhufnage]
#09/04/2013  - 2.2 - Using Suspect and Mtokens
#12/20/2013  - 2.3 - Updated hostnames
package require Expect
package require tile
#package require registry
#package require Suspect
#suspect::Import


global cotvncdir
wm title . "CAEN VNC v2.3"
wm iconname . "CAENVNC"
wm resizable . 0 0

set URL "http://www.engin.umich.edu/caen/connect/vnc.html"
set v_currentresh "[expr {[winfo screenwidth .]}]"
set v_currentresv "[expr {[winfo screenheight .]}]"
#set v_username "$::env(USERNAME)"
set v_username "$::env(USER)"
set cotvncdir "$::env(COTVNCDIR)"
set v_token ""

set v_password ""
set v_hostname "login-course.engin.umich.edu"

#####################################################################
# Configure Hostname label and text box
#####################################################################
frame  .hostname -bd 2
label  .hostname.label -text Hostname: -width 10 -anchor w
ttk::combobox .hostname.combobox -textvariable v_hostname -values "login-course.engin.umich.edu oncampus-course.engin.umich.edu restricted-course.engin.umich.edu" 
pack   .hostname.label -side left
pack   .hostname.combobox  -side left

#####################################################################
# Configure Login label and text box
#####################################################################
frame  .username -bd 2
label  .username.label -text Username: -width 10 -anchor w
entry  .username.entry -relief sunken
.username.entry config -textvariable v_username 
pack   .username.label -side left
pack   .username.entry -side left

#####################################################################
# Configure Password label and text box
#####################################################################
frame  .password -bd 2
label  .password.label -text Password: -width 10 -anchor w
entry  .password.entry -relief sunken
.password.entry config -textvariable v_password -show "*" 
pack   .password.label -side left
pack   .password.entry -side left
#####################################################################
# Configure MToken label and text box
#####################################################################
frame  .token -bd 2
label  .token.label -text MToken: -width 10 -anchor w
entry  .token.entry -relief sunken
.token.entry config -textvariable v_token
pack   .token.label -side left
pack   .token.entry -side left
#####################################################################
# Configure Resolution label and list box
#####################################################################
frame  .screenres -bd 2
label  .screenres.reslabel -text Resolution: -width 10 -anchor w
ttk::combobox .screenres.comboboxh -width 5 -textvariable v_currentresh -values "800 1024 1280 1400 1600 1680 1920 2560"
label  .screenres.xlabel -text x -width 1 -anchor w
ttk::combobox .screenres.comboboxv -width 5 -textvariable v_currentresv -values "600 768 800 1024 1050 1200 1600"
pack   .screenres.reslabel -side left
pack   .screenres.comboboxh  -side left
pack   .screenres.xlabel -side left
pack   .screenres.comboboxv  -side left

####################################################################
# Configure Status label
#####################################################################
frame	.status -bd 2
label	.status.label
pack	.status.label -side left
.status.label config -text "Awaiting credentials..."

#####################################################################
# Configure Buttons
#####################################################################
frame	.buttons -bd 2
button	.buttons.ok -text "Connect" -borderwidth 1m -command "showScreen \$v_hostname \$v_username \$v_password \$v_token"
button	.buttons.dismiss -text "Cancel" -command "destroy ."
button	.buttons.help -text "Help" -command "exec [auto_execok start] {$URL}"
bind	. <Return> ".buttons.ok invoke"
bind	. <F1> ".buttons.help invoke"
pack	.buttons.ok .buttons.dismiss .buttons.help -side left -expand 1
pack	.buttons -side bottom -fill x -pady 2m

#####################################################################
# Pack everything into the window
#####################################################################
pack	.hostname .username .password .screenres .status .buttons -fill x
##
#
##
proc showMToken {} {
global v_hostname
	if {[string match *restricted* $v_hostname]} {
		pack .token -after .password -fill x
	} else {
		pack forget .token
	}
}
bind . <<ComboboxSelected>> {showMToken}
bind .hostname.combobox <KeyRelease> {showMToken}

#####################################################################
# Focus and Raise window
#####################################################################
focus .password.entry
raise .

set wx [expr {([winfo screenwidth .]-[winfo width .])/2}]
set wy [expr {([winfo screenheight .]-[winfo height .])/2}]
wm geometry . +$wx+$wy

#####################################################################
# Let's run it...
#####################################################################
proc showScreen {ss_host ss_user ss_pass ss_token} {
global v_currentresh
global v_currentresv
global env
global cotvncdir

if { [string is integer -strict $v_currentresh] == 0 } {
	.status.label config -text "Fix horizontal resolution!"
	focus .screenres.comboboxh
	return
}
if { [string is integer -strict $v_currentresv] == 0 } {
	.status.label config -text "Fix vertical resolution!"
	focus .screenres.comboboxv
	return
}


#set port $resolution($v_currentres)
.buttons.ok config -state disabled

set env(CAENVNCSIZE) ${v_currentresh}x${v_currentresv}
set env(CVNCSIZE) ${v_currentresh}x${v_currentresv}

set port   85

set fs " "
if { [string compare "$v_currentresh" "[expr {[winfo screenwidth .]}]"] == 0 } { 
   if { [string compare "$v_currentresv" "[expr {[winfo screenheight .]}]"] == 0 } {
	set fs "-FullScreen"
   }
}
set timeout -1

.status.label config -text ""
.status.label config -text "Connecting $ss_host"


set env(CVNCUSER) $ss_user


#exp_spawn ssh -L $port:localhost:$port $ss_user@$ss_host "echo hello\;cat"

exp_spawn [file join "$cotvncdir" caenvnc.sh] -c $ss_host 

#expect {
#	"Are you sure*"  	{exp_send "yes\r"}
#	"$ss_user*" 		{exp_send "$ss_pass\r"}
#	"hello*"  			{wm withdraw .;exec  $::env(COTVNCDIR)/../VNC\ Viewer.app/Contents/MacOS/vncviewer WarnUnencrypted=0  127.0.0.1:85 2>>/dev/null  ; destroy .;exp_close;exit}
#       }
#expect {
#	"$ss_user*" 		{exp_send "$ss_pass\r"}
#	"hello*"  			{wm withdraw .;exec  $::env(COTVNCDIR)/../VNC\ Viewer.app/Contents/MacOS/vncviewer WarnUnencrypted=0  127.0.0.1:85 2>>/dev/null ; destroy .;exp_close;exit}
#       }
#expect {
#	"Permission*" 		{exp_close; showErr}
#	"hello*"  			{wm withdraw .;exec  $::env(COTVNCDIR)/../VNC\ Viewer.app/Contents/MacOS/vncviewer WarnUnencrypted=0 127.0.0.1:85 2>>/dev/null  ; destroy .;exp_close;exit}
#       }

set pwcount 0
set done 0
while { $done == 0 } {

expect {
         "Are you sure*"         {exp_send "yes\r"}
         "MToken*"	{exp_send  "$ss_token\r"}
         "Password*"              {exp_send "$ss_pass\r";set pwcount [expr {$pwcount + 1}]}
         "password*"              {exp_send "$ss_pass\r";set pwcount [expr {$pwcount + 1}]}
         "hello*"                {wm withdraw .;exec  $::env(COTVNCDIR)/../VNC\ Viewer.app/Contents/MacOS/vncviewer WarnUnencrypted=0  127.0.0.1:85 2>>/dev/null ; destroy .;exp_close;exit}
       }
 if { $pwcount > 1 } {showErr "Access denied!"; set done 1}
}

	   
.buttons.ok config -state normal	 
}

#####################################################################
# Error
#####################################################################
proc showErr {str_message} {
        .status.label config -text [string range $str_message 0 35]
        .buttons.ok config -state normal
}
proc showEOF {} {
        set done 1
        .status.label config -text "Unexpected Error!"
        .buttons.ok config -state normal
}
proc showTimeout {} {
        set done 1
        .status.label config -text "Timeout!"
        .buttons.ok config -state normal
}


