BEGIN { }

{
    if (match ($0, /^##### (\w+) ([0-9])(.*)$/, fields) && match ($0, /^!\[/) == 0) {
        type = fields[1]
        number = fields[2]
        title = fields[3]

        line = "__" type " " number "__" title
    }
    else
        line = $0

    print line
}

