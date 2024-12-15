#!/bin/bash

i=0
echo running ...
start_time=$(date +%s.%N)  
for file in ./Shakespeare/*; do
    ./main2 "inserer" "0" "$file"
    mv pat.json "./Etude_exp/pat${i}.json" 
    
    if [ $i -eq 1 ]; then
        prev=$((i - 1))  # Calculate the previous index
        ./main2 fusion "0" "./Etude_exp/pat${i}.json" "./Etude_exp/pat${prev}.json"
        mv pat.json "./Etude_exp/patres.json"
    fi

    if [ $i -gt 1 ]; then
        ./main2 fusion "0" "./Etude_exp/pat${i}.json" "./Etude_exp/patres.json"
        mv pat.json "./Etude_exp/patres.json"
    fi

    i=$((i + 1))  
done

end_time=$(date +%s.%N)

# Calculate the elapsed time
elapsed_time=$(echo "$end_time - $start_time" | bc)

echo "Fusion complete. Final result saved in patres.json"
echo "Total time taken: ${elapsed_time} seconds"