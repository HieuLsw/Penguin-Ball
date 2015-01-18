#!/usr/bin/ruby

require 'syslog'

pdir = ARGV[0]

#this seems to work too...
#puts Dir.getwd

log = Syslog.open("BigSquirrelly")
log.warning("Program Starting")
rdir = pdir.gsub(':','\ ')

bdir = rdir + 'bin/'
rdir = '/usr/bin/wish ' + rdir + 'bin/sshnew.tcl' + ' ' + bdir


log.warning("Executing Command: " + rdir)
#system(rdir)
exec(rdir)
log.warning("Exiting now.")
