BEGIN { }

{
    if (match ($0, /^<p align=center>List p[0-9]c[0-9]{1,2}-(\w+)(.*)<\/p>$/, fields)) {
        line = "##### List " fields[1] fields[2]
        print line
    }
    else
        print $0
}

