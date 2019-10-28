BEGIN { in_code = 0 }

/^```/  {
    if (in_code == 0) {
        in_code = 1
    }
    else {
        in_code = 0
        print $0
    }
}

function is_proper_name(name)
{
    if (match(name, /(.+)(\W)$/, fields)) {
        name = fields[1] " "
    }
    else
        name = name " "

    return index ("MiniGUI mGUtils mGEff mGPlus mGNCS mGNCS4Touch mStudio miniStudio VxWorks Linux RT-Thread ThreadX uC/OS-II FreeRTOS RTEMS", name)
}

{
    line = ""

    if (in_code) {
#        if ($1 == "```cplusplus")
#            print "```cpp"
#        else
#            print $0
    }
    else {
        if (match ($0, /^<br \/>/)) {
            print ""
            next
        }
        else if (match ($0, /^\|(.*)$/, fields)) {
            $0 =  "| " fields[1]
        }
        else if (match ($0, /^(<center>)(.*)(<\/center>)$/, fields)) {
            print ""
            $0 = fields[2]
        }
        else if (match ($0, /^(<center>)(.*)(<br \/><br \/>)$/, fields)) {
            print ""
            $0 = fields[2]
        }
        else if (match ($0, /^<center>$/)) {
            print ""
            next
        }
        else if (match ($0, /^<\/center>$/)) {
            print ""
            next
        }
        else if (match ($0, /\s*<img /)) {
            for (i = 2; i <= NF; i++) {
                if (match ($i, /^(alt)="(.+)"/, fields)) {
                    print ""
                    print "![alt](figures/" fields[2] ")"
                    print ""
                    next
                }
            }
        }
        else if (match ($0, /^#/)) {
            if (match ($2, /[0-9]+/)) {
                $2 = ""
            }
            if (match ($2, /[0-9]+(\.[0-9]+)+/)) {
                $2 = ""
            }
        }

        nr_chars = 0
        for (i = 1; i <= NF; i++) {
            if (is_proper_name($i)) {
                # do nothing
            }
            else if ($i == "mg-samples" ) {
                $i = "`" $i "`"
            }
            else if ($i == "mginit" ) {
                $i = "`" $i "`"
            }
            else if (match ($i, /^[A-Z]{2,}$/)) {
                $i = "`" $i "`"
            }
            else if (match ($i, /^\(([A-Z]{2,}.+)\)$/, fields)) {
                $i = "(`" fields[1] "`)"
            }
            else if (match ($i, /^([A-Z]+_\w*),/, fields)) {
                $i = "`" fields[1] "`,"
            }
            else if (match ($i, /^([A-Z]+_\w*)\./, fields)) {
                $i = "`" fields[1] "`."
            }
            else if (match ($i, /^[A-Z]([a-z]*)[A-Z]/)) {
                $i = "`" $i "`"
            }
            else if (match ($i, /^[A-Z]+_/)) {
                $i = "`" $i "`"
            }
            else if (match ($i, /^[a-z]+_/)) {
                $i = "`" $i "`"
            }
            else if (match ($i, /^[a-z]+[A-Z]/)) {
                $i = "`" $i "`"
            }
            else if (match ($i, /^Table$/) && match ($(i+1), /([0-9]+\.)([0-9]+)(.*)$/, fields)) {
                $(i+1) = fields[2] fields[3]
            }
            else if (match ($i, /^Figure$/) && match ($(i+1), /([0-9]+\.)([0-9]+)(.*)$/, fields)) {
                $(i+1) = fields[2] fields[3]
            }
            else if (match ($i, /^Fig.$/) && match ($(i+1), /([0-9]+\.)([0-9]+)(.*)$/, fields)) {
                $i = "Figure"
                $(i+1) = fields[2] fields[3]
            }
            else if (match ($i, /^List$/) && match ($(i+1), /([0-9]+\.)([0-9]+)(.*)$/, fields)) {
                $(i+1) = fields[2] fields[3]
            }

            if ($i == "")
                continue

            if (match ($0, /^\|(.*)$/)) {
                if (i == NF) {
                    line = line $i
                }
                else {
                    line = line $i " "
                }
            }
            else {
                # hard wrap for a normal paragraph
                if ((nr_chars + length ($i)) < 80) {

                    if (i == NF) {
                        line = line $i
                        nr_chars += length ($i)
                    }
                    else {
                        line = line $i
                        nr_chars += length ($i)

                        if (nr_chars + length ($(i+1)) < 80) {
                            line = line " "
                            nr_chars += 1
                        }
                    }
                }
                else {
                    print line
                    line = $i " "
                    nr_chars = length($i) + 1
                }
            }
        }

        print line
    }
}

