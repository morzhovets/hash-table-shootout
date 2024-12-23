import sys, os, subprocess, signal

programs = [
    'momo_map_1',
    'momo_map_2',
    'momo_map_3',
    'momo_map_4',
    'momo_map_0',
]

minkeys  =  1*1000*1000
maxkeys  =  5*1000*1000
interval =  1*1000*1000
best_out_of = 4

if len(sys.argv) > 1:
    benchtypes = sys.argv[1:]
else:
    benchtypes = (
                  'insert_int', 'find_existing_int', 'delete_int',
                  'iterate_int', 
                  'insert_smallstring', 'find_existing_smallstring', 'delete_smallstring', 
#                  'insert_string', 'find_existing_string', 'delete_string',
                  )

for benchtype in benchtypes:
    nkeys = minkeys
    while nkeys <= maxkeys:
        dict = {}

        for attempt in range(best_out_of):
            for program in programs:
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

                    if program not in dict or runtime < dict[program][0]:
                        dict[program] = (runtime, line)

        for program in programs:
            if program in dict:
                print(dict[program][1])
        print(flush=True)

        nkeys += interval
