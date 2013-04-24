def print_avl(from, to)
  #print [from, to].inspect
  val = (to - from + 1) / 2.0 + from

  return if from >= to

  puts val.floor
  print_avl(from, val.floor - 1)
  print_avl(val.floor, to)
end

print_avl(99_999, 999_999)
