import sys, os, subprocess, signal

programs = [
    'momo_unordered_map_1',
    'momo_unordered_map_2',
    'momo_unordered_map_3',
    'momo_unordered_map_0',
]

minkeys  =  5*1000*1000
maxkeys  =  9*1000*1000
interval =  1*1000*1000
best_out_of = 4

if len(sys.argv) > 1:
    benchtypes = sys.argv[1:]
else:
    benchtypes = (
                  'randomfull', 'randomfullread', 'randomfullreadmiss',
                  'iteration', 'delete', 
                  'insertsmallstring', 'readsmallstring', 'readsmallstringmiss', 'deletesmallstring', 
#                  'insertstring', 'readstring', 'readstringmiss', 'deletestring',
                  )

for benchtype in benchtypes:
    nkeys = minkeys
    while nkeys <= maxkeys:
        print(flush=True)

        for program in programs:
            fastest_attempt = 1000000
            fastest_attempt_data = ''

            for attempt in range(best_out_of):
                proc = subprocess.Popen(['./build/'+program, str(nkeys), benchtype], stdout=subprocess.PIPE)

                # wait for the program to fill up memory and spit out its "ready" message
                try:
                    runtime = float(proc.stdout.readline().strip())
                except:
                    runtime = 0

                ps_proc = subprocess.Popen(['ps up %d | tail -n1' % proc.pid], shell=True, stdout=subprocess.PIPE)
                nbytes = int(ps_proc.stdout.read().split()[4]) * 1024
                ps_proc.wait()

                os.kill(proc.pid, signal.SIGKILL)
                proc.wait()

                if nbytes and runtime: # otherwise it crashed
                    line = ','.join(map(str, [benchtype, nkeys, program, nbytes, "%0.6f" % runtime]))

                    if runtime < fastest_attempt:
                        fastest_attempt = runtime
                        fastest_attempt_data = line

            if fastest_attempt != 1000000:
                print(fastest_attempt_data, flush=True)

        nkeys += interval
