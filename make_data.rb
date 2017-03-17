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
  `mkdir -p submission/data/#{s}`
  `cp #{input.join " "} submission/data/#{s}`
  `cp #{output.join " "} submission/data/#{s}`
}

Dir.chdir("submission/data") {
  Dir.glob("**/*.diff").each { |diff|
    `mv #{diff} #{diff.sub('.diff', '.out')}`
  }
}
