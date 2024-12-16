#!/bin/bash

i=0
j=0
echo running for patricia tree ...
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
echo "Fusion complete. Final result saved in patres.json"

echo running for hybrid-trie ...

start_time2=$(date +%s)  
for file in ./Shakespeare/*; do
    echo "inserting $file words"
    ./main2 "inserer" "1" "$file"
    mv hyb.json "./Etude_exp/hyb${j}.json" 
    

    ### Should do the same fusion as for patricia to get everything in the same H-trie
    ### but fusion is not defined for this structure

    j=$((j + 1))  
done

end_time2=$(date +%s)

# Calculate the elapsed time
elapsed_time=$(echo "$end_time - $start_time" | bc)
elapsed_time2=$(echo "$end_time2 - $start_time2" | bc)


echo "Total time taken for patricia: ${elapsed_time} seconds"
echo "Total time taken for hybrid-trie: ${elapsed_time2} seconds"