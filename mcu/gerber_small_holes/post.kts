import java.io.File

val outputDir = File("./out")
var nextTool = 1;
for(f in outputDir.listFiles()?.filter { it.name.endsWith(".ngc") } ?: emptyList()) {
    val newFile = f.readLines().map { line ->
        val p = line.split(' ').map { it.trim() }.toMutableList()
        val newLine= if(p.firstOrNull()?.startsWith("T") == true && p.getOrNull(0)?.getOrNull(1)?.isDigit() == true) {
            if(f.name == "front.ngc" || f.name == "back.ngc")
                p[0] = "T1"
            else if(f.name == "milldrill.ngc" || f.name == "outline.ngc")
                p[0] = "T2"
            else
                throw Exception(f.name)
            nextTool++
            p.joinToString(" ", prefix = "", postfix = "")
        } else {
            line
        }
        if(line.startsWith("T")) println("${f.name}: L $line ${p.joinToString()} NL ${newLine}")
        newLine
    }
    f.writeText(newFile.joinToString(System.lineSeparator()))
}
