// Standard version

in = fopen(FileName,"r");
while (fscanf(in, "%d", &item) == 1) {
   if (!SetMember(seenItems, item)) {
      SetInsert(seenItems, item);
      process item
   }
}
fclose(in);

// Alternative version (using continue)

in = fopen(FileName,"r");
while (fscanf(in, "%d", &item) == 1) {
   if (SetMember(seenItems, item)) continue;
   SetInsert(seenItems, item);
   process item
}
fclose(in);
