BEGIN { in_code = 0; printed = 0 }

/^```/  {
    if (in_code == 0) {
        in_code = 1
    }
    else {
        in_code = 0
        print $0
    }
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
        nr_chars = 0

        if (match ($0, /^<br \/>/)) {
            print ""
            next
        }
        else if (match ($0, /^(<center>)(.*)(<\/center>)$/, fields)) {
            $0 = fields[2]
        }
        else if (match ($0, /^(<center>)(.*)(<br \/><br \/>)$/, fields)) {
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
                    print "![alt](figures/" fields[2] ")"
                    next
                }
            }
        }
        else if (match ($0, /^#/)) {
            if (match ($2, /[0-9]+(\.[0-9]+)+/)) {
                $2 = ""
            }
        }

        for (i = 1; i <= NF; i++) {
            if (match ($i, /_/)) {
                $i = "`" $i "`"
            }
            else if (match ($i, /[A-Z]{2,}/)) {
                $i = "`" $i "`"
            }
            else if (match ($i, /^[A-Z]([a-z]*)[A-Z]/)) {
                $i = "`" $i "`"
            }
            else if (match ($i, /^Table ([0-9]+\.)([0-9]+)/, fields)) {
                $i = "Table " fields[2]
            }
            else if (match ($i, /^Fig. ([0-9]+\.)([0-9]+)/, fields)) {
                $i = "Figure " fields[2]
            }
            else if (match ($i, /^List ([0-9]+\.)([0-9]+)/, fields)) {
                $i = "List " fields[2]
            }

            line = line $i " "
        }

        print line
    }
}
