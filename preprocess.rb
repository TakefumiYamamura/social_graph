hash = {}
Dir.glob("twitter/*.edges") do |file| 
	File.open(file) do |io|
		io.each_line do |line|
			arr = line.split(" ").map{|v| v.to_i}
			unless hash.has_key?(arr[0])
				hash[arr[0]] = []
			end

			hash[arr[0]] << arr[1];
		end
	end
end

edge_count = 0
hash.each do |key, val|
	File.open("processed_twitter/#{key}.txt", "w") do |file|
		val.each do |ele|
			file.puts ele
			edge_count += 1
		end  
	end
end

puts edge_count
