#!/bin/csh

foreach i (1 2 3 4 5 6 10 12 15 20 24 30 40 50 60 72 80 90 100)
	cd T$i
	foreach i (3 4 5 6 7 8 9 10 11 12 13 14)
        	tail -1 L*L$i >> time
	end
	cd ..
end

