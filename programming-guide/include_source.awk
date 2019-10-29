BEGIN { }

# %INCLUDE{"%ATTACHURL%/helloworld.c.txt" pattern="^.*?// START_OF_INCS(.*?)// END_OF_INCS.*"}%

{
    if (match ($0, /^%INCLUDE\{"%ATTACHURL%\/(\w+)\W/, fields)) {
        source_file = "samples/" fields[1] ".c"
        if (match ($0, /.+pattern=".+START_(\w+)\W.+END_(\w+)\W/, fields)) {
            start_tag = "START_" fields[1]
            end_tag   = "END_" fields[2]
#            print "Include source between " start_tag " and " end_tag " from " source_file " here..."

            started = 0
            while ((getline line < source_file) > 0) {

                if (index (line, start_tag) != 0) {
                    started = 1
                    continue
                }
                else if (index (line, end_tag) != 0) {
                    started = 0
                }

                if (started) {
                    print line
                }
            }

            close (source_file)
        }
        else {
#            print "Include all source from " source_file " here..."
            while ((getline line < source_file) > 0)
                print line
            close (source_file)
        }
    }
    else
        print $0
}

