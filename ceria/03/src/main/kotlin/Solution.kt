import java.io.File;

val charPriorities = "-abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".toList()


fun main(args : Array<String>) {
    var input = File(args.first()).readLines()
    println("Solution 1: ${solution1(input)}")
    println("Solution 2: ${solution2(input)}")
}

private fun solution1(input: List<String>) :Int {
    return input.map{
        it.chunked(it.length / 2)
    }.map { 
        it.first().toList().intersect(it.last().toList()).first() 
    }.map{ 
        charPriorities.indexOf(it) 
    }.sum()
}
    
private fun solution2(input: List<String>) :Int {
    var priorities = mutableListOf<Char>()
    repeat(input.size / 3) { count ->
        var index = count * 3
        var elf1 = input.get(index).toList()
        var elf2 = input.get(index + 1).toList()
        var elf3 = input.get(index + 2).toList()
        priorities.add(elf1.intersect(elf2).intersect(elf3).first())
    }
   return priorities.map { charPriorities.indexOf(it) }.sum()
}

