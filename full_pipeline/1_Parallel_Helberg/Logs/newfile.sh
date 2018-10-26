#!/bin/csh

set echo

foreach i (`cat tcounts.txt`) 
	`ll T$i`|sort -k9 -n 
end

