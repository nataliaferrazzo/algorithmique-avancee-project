#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <command> <trie_type> [additional arguments]"
    exit 1
fi

command=$1
trie_type=$2
echo "in the script"

case $command in
    create)
        echo "in the good case"
        ./main2 create "$trie_type" "$3" "$4"
        echo "call finish"
        ;;
    insert)
        ./main2 insert "$trie_type" "$3" "$4"
        ;;
    delete)
        ./main2 delete "$trie_type" "$3" "$4"
        ;;
    *)
        echo "Unknown command: $command"
        exit 1
        ;;
esac
