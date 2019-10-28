BEGIN { }

{
    if (match ($0, /^<img /)) {
        for (i = 2; i <= NF; i++) {
            if (match ($i, /^(alt)="(.+)"/, fields)) {
                print "![alt](figures/" fields[2] ")"
            }
        }
    }
    else
        print $0
}

