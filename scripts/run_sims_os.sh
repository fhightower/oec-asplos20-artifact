#!/bin/bash
#
# run_sims_os.sh
# A bash script that runs the orbit-spaced simulations
#
# Written by Bradley Denby
# Other contributors: None
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication with this
# software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

../artifacts/sim-os/scripts/run_os_scenarios.sh &
echo "OS simulations are running in the background."
echo "It may be awhile before they complete, check with 'top'."