import java.io.File;

fun main(args : Array<String>) {
   
    var input = mutableListOf<List<Int>>()
    File(args.first()).readLines().forEach {
	var row = it.toList().map{ it.digitToInt() }
	input.add(row)
    }

    println("Solution 1: ${solution1(input)}")
    println("Solution 2: ${solution2(input)}")
}

private fun solution1(input: List<List<Int>>) :Int {
   // left and right columns are input.size
   var visibleCount = input.size * 2
   
   // top and bottom rows are intput.get(0) and input.get(input.size - 1)
   // minus the corners (so minus 4)
   visibleCount += ((input.get(0).size * 2) - 4)

    // skip iterating the top and bottom edges
    for (y in 1..input.size - 2) {
        var row = input.get(y)

        // skip iterating the outside left and right edges
        for (x in 1..row.size - 2) {
	    var tree = row.get(x)

	    // inspect the trees looking up
	    var upVisible = input.subList(0, y).map{ it.get(x) }.filter{ it > tree - 1 }.isEmpty()

	    // inspect the trees looking down
	    var downVisible = input.subList(y+1, input.size).map{ it.get(x) }.filter{ it > tree - 1}.isEmpty()

            // inspect the trees looking left
	    var leftVisible = row.subList(0, x).filter{ it > tree - 1 }.isEmpty()

            // inspect the trees looking right
	    var rightVisible = row.subList(x+1, row.size).filter{ it > tree - 1 }.isEmpty()

	    if (upVisible || downVisible || leftVisible || rightVisible) {
		visibleCount++
	    }
         }
    }

   return visibleCount
}

private fun solution2(input: List<List<Int>>) :Int {
    var scenicScore = 0

    for (y in 0..input.size - 1) {
        var row = input.get(y)

        for (x in 0..row.size - 1) {
            var tree = row.get(x)

	     // inspect the trees looking up
            var upScenicScore = 0
	    val lookingUp = input.subList(0, y).map{ it.get(x) }
	    for (up in lookingUp.size - 1 downTo 0) {
		upScenicScore++
		if (lookingUp.get(up) >= tree) {
		    break
		}
	    }

            // inspect the trees looking down
            var downScenicScore = 0
	    val lookingDown = input.subList(y + 1, input.size).map{ it.get(x) }
	    for (down in 0..lookingDown.size - 1) {
		downScenicScore++
		if (lookingDown.get(down) >= tree) {
                    break
                }
	    }

            // inspect the trees looking left
            var leftScenicScore = 0
	    val lookingLeft = row.subList(0, x)
	    for (left in lookingLeft.size - 1 downTo 0) {
		leftScenicScore++
		 if (lookingLeft.get(left) >= tree) {
                    break
                }
	    }

            // inspect the trees looking right
            var rightScenicScore = 0
	    val lookingRight = row.subList(x+1, row.size)
	    for (right in 0..lookingRight.size - 1) {
		rightScenicScore++
		if (lookingRight.get(right) >= tree) {
                    break
                }
	    }

	    val newScenicScore = upScenicScore * downScenicScore * leftScenicScore * rightScenicScore
	    if (newScenicScore > scenicScore) {
		scenicScore = newScenicScore
	    }
	}
    }

    return scenicScore
}
