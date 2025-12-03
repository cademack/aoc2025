let pattern = 
	Str.regexp
		(* {|(\d+)\1+|} *)
		"\\(.+\\)\\1+$"

let value_of_value value = 
	let strn = string_of_int value in 
	if Str.string_match pattern strn 0 then
		begin
			print_endline @@ string_of_int value;
			value
		end
	else 0

	(* if strlen mod 2 = 0 && strlen > 0 then
		let first_half = String.sub strn 0 (strlen / 2) in
		let second_half = String.sub strn (strlen / 2) (strlen / 2) in
		if first_half = second_half then
			value
		else 0
	else 0  *)

let value_of_range lower higher =
	let rec ticker acc cur_val =
		if cur_val > higher then
			acc
		else
			ticker (acc + value_of_value cur_val) (cur_val + 1) 
	in ticker 0 lower

let sum_ranges in_ranges =
	let rec range_summer acc = function
		| [] -> acc
		| r :: rest ->
			let split_string = Str.split (Str.regexp "-") r in
			(* print_endline @@ ":" ^ (List.nth split_string 0); *)
			let lower = int_of_string (List.nth split_string 0) in
			(* print_endline @@ ":" ^ (List.nth split_string 1); *)
			let higher = int_of_string (List.nth split_string 1) in
			let range_value = value_of_range lower higher in
			range_summer (acc + range_value) rest
	in range_summer 0 in_ranges

let () =
	let input_text = In_channel.with_open_text "../input.txt" In_channel.input_all in
	let ranges = Str.split (Str.regexp ",") input_text in
	print_endline @@ string_of_int (sum_ranges ranges)
