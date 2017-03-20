#!/usr/bin/env ruby

problems = [
  'Tournament',
  'Range_Num',
  'Tree_Tree',
  'Password',
  'Graduation_Ceremony',
  'Card_Game',
  'Change_of_Buses',
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

checker_dir = 'submission/checker/C'
`mkdir -p #{checker_dir}`
`cp Tree_Tree/tests/judge.cc #{checker_dir}`
`cp Tree_Tree/tests/testlib.h #{checker_dir}`
`cp Tree_Tree/tests/constraints.hpp #{checker_dir}`
