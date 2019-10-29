BEGIN { }

function map_link(link)
{
    switch (link) {
    case "MStudioMGNCSV1dot0PGENAppA":
    case "MStudioMGNCSV1dot0PGAppA":
        link = "MiniGUIProgGuideAppendixA.md"
        break

    case "MStudioMGNCSV1dot0PGENAppB":
    case "MStudioMGNCSV1dot0PGAppB":
        link = "MiniGUIProgGuideAppendixB.md"
        break

    case "MStudioMGNCSV1dot0PGENAppC":
    case "MStudioMGNCSV1dot0PGAppC":
        link = "MiniGUIProgGuideAppendixC.md"
        break

    case "MStudioMGNCSV1dot0PGENP2C1":
    case "MStudioMGNCSV1dot0PGP2C1":
        link = "MiniGUIProgGuidePart2Chapter02.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C2":
    case "MStudioMGNCSV1dot0PGP2C2":
        link = "MiniGUIProgGuidePart2Chapter03.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C3":
    case "MStudioMGNCSV1dot0PGP2C3":
        link = "MiniGUIProgGuidePart2Chapter04.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C4":
    case "MStudioMGNCSV1dot0PGP2C4":
        link = "MiniGUIProgGuidePart2Chapter05.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C5":
    case "MStudioMGNCSV1dot0PGP2C5":
        link = "MiniGUIProgGuidePart2Chapter06.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C6":
    case "MStudioMGNCSV1dot0PGP2C6":
        link = "MiniGUIProgGuidePart2Chapter07.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C7":
    case "MStudioMGNCSV1dot0PGP2C7":
        link = "MiniGUIProgGuidePart2Chapter08.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C8":
    case "MStudioMGNCSV1dot0PGP2C8":
        link = "MiniGUIProgGuidePart2Chapter09.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C9":
    case "MStudioMGNCSV1dot0PGP2C9":
        link = "MiniGUIProgGuidePart2Chapter10.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C10":
    case "MStudioMGNCSV1dot0PGP2C10":
        link = "MiniGUIProgGuidePart2Chapter11.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C11":
    case "MStudioMGNCSV1dot0PGP2C11":
        link = "MiniGUIProgGuidePart2Chapter12.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C12":
    case "MStudioMGNCSV1dot0PGP2C12":
        link = "MiniGUIProgGuidePart2Chapter13.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C14":
    case "MStudioMGNCSV1dot0PGP2C14":
        link = "MiniGUIProgGuidePart2Chapter15.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C15":
    case "MStudioMGNCSV1dot0PGP2C15":
        link = "MiniGUIProgGuidePart2Chapter16.md"
        break;

    case "MStudioMGNCSV1dot0PGENP2C16":
    case "MStudioMGNCSV1dot0PGP2C16":
        link = "MiniGUIProgGuidePart2Chapter17.md"
        break;

    case "MStudioNCSSPGENV1dot0Chapter15":
        link = "MiniGUIProgGuidePart2Chapter17.md"
        break;

    case "MStudioMGNCSV1dot0PGP2C":
        link = "MiniGUIProgGuidePart2Chapter15.md"
        break;

    case "MStudioMGNCSV1dot0PGP2C13":
        link = "MiniGUIProgGuidePart2Chapter14.md"
        break;

    default:
        if (match(link, /^MiniGUIProgGuidePart.+md$/) == 0) {
            link = link ".md"
        }
        break;
    }

    return link
}

function convert_link_with_anchor(link, anchor)
{
    link = map_link(link)

    sub(/\.md$/, "", anchor)
    sub(/_/, "", anchor)
    anchor = tolower(anchor)

    return link "#" anchor
}

function convert_link(link)
{
    link = map_link(link)
    return link
}

#Please refer to `mRadioButton` in [Button Series Control Class](MStudioMGNCSV1dot0PGENP2C5).

{
    if (match ($0, /^(.*)\[(.+)\]\(([^\s]+)\)(.*)$/, fields) && match ($0, /^!\[/) == 0) {
        link = fields[3]

        if (link == "README.md") {
            # do nothing
        }
        else if (match (link, /(.+)\#(.+)/, parts)) {
            link = convert_link_with_anchor(parts[1], parts[2])
        }
        else {
            link = convert_link(link)
        }

        line = fields[1] "[" fields[2] "](" link ")" fields[4]
    }
    else
        line = $0

    print line
}

