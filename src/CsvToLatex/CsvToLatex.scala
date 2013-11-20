import java.io.{PrintWriter, File}

object CsvToLatex {
  def main(args: Array[String]) {
    if ( args.length != 1) {
      println("Error: Wrong input arguments.\n Usage: java csvTolatex <path/to/file>")
      sys.exit(1)
    }
    val app: CsvToLatex = new CsvToLatex()
    app.output(app.convert(args(0)), args(0)+".output")
  }
}

class CsvToLatex {
  def convert(input: String) : String = {
    val output = new StringBuilder().append("\\begin{tabular}{")

    val len = scala.io.Source.fromFile(input).getLines().toList(1).split(",").length
    for ( s <- 0 to len - 2 )
      output.append("l | ")
    output.append("l}\n  ")

    for ( s <- 0 to len - 2 )
      output.append("A & ")
    output.append("A\\\\\n  \\hline\n")

    for ( line <- scala.io.Source.fromFile(input).getLines() ) {
      output.append("  ")
      val numbers = line.split(",")
      for ( n <- numbers ) if ( !n.isEmpty )
        output.append(if ( n != numbers(numbers.length - 1) ) n + " &" else n + "\\\\\n")
    }
    output.append("\\end{tabular}").toString()
  }

  def output(output: String, name: String) {
    val writer = new PrintWriter(new File(name))

    writer.write(output)
    writer.close()
  }
}