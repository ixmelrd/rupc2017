#!/usr/bin/env ruby

problems = [
  'Tournament',
  'Weight_Range',
  'Fractal_Tree',
  'Password',
  'Graduation_Ceremony',
  'Card_Game',
  'Rainy_Bus_Stops',
  'Jump_Party',
  'Islands_Survival',
  'Energy_Drink',
  "AORs_Score"
]

problems.zip('A'..'Z').each { |p, s|
  input  = Dir.glob("#{p}/rime-out/tests/*.in")
  output = Dir.glob("#{p}/rime-out/tests/*.diff")
  dst_dir = "submission/data/#{s}_#{p}"
  `mkdir -p #{dst_dir}`
  `cp #{input.join " "} #{dst_dir}`
  `cp #{output.join " "} #{dst_dir}`
}

Dir.chdir("submission/data") {
  Dir.glob("**/*.diff").each { |diff|
    `mv #{diff} #{diff.sub('.diff', '.out')}`
  }
}

checker_dir = 'submission/checker/C_Fractal_Tree'
`mkdir -p #{checker_dir}`
`cp Fractal_Tree/tests/judge.cc #{checker_dir}`
`cp Fractal_Tree/tests/testlib.h #{checker_dir}`
`cp Fractal_Tree/tests/constraints.hpp #{checker_dir}`
