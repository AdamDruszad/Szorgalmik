import os, streams, math, strutils

type
  Csomopont = ref object
    betu: char
    balNulla: Csomopont
    jobbEgy: Csomopont

  LZWBinFa = ref object
    gyoker: Csomopont
    fa: Csomopont
    melyseg, maxMelyseg, atlagosszeg, atlagdb: int
    atlag, szorasosszeg, szoras: float

proc ujCsomopont(b: char = '/'): Csomopont =
  new(result)
  result.betu = b
  result.balNulla = nil
  result.jobbEgy = nil

proc ujLZWBinFa(): LZWBinFa =
  new(result)
  result.gyoker = ujCsomopont('/')
  result.fa = result.gyoker

proc `<<`(bf: LZWBinFa, b: char) =
  if b == '0':
    if bf.fa.balNulla == nil:
      bf.fa.balNulla = ujCsomopont('0')
      bf.fa = bf.gyoker
    else:
      bf.fa = bf.fa.balNulla
  else:
    if bf.fa.jobbEgy == nil:
      bf.fa.jobbEgy = ujCsomopont('1')
      bf.fa = bf.gyoker
    else:
      bf.fa = bf.fa.jobbEgy

proc rmelyseg(bf: LZWBinFa, elem: Csomopont) =
  if elem != nil:
    inc bf.melyseg
    if bf.melyseg > bf.maxMelyseg:
      bf.maxMelyseg = bf.melyseg
    bf.rmelyseg(elem.jobbEgy)
    bf.rmelyseg(elem.balNulla)
    dec bf.melyseg

proc getMelyseg(bf: LZWBinFa): int =
  bf.melyseg = 0
  bf.maxMelyseg = 0
  bf.rmelyseg(bf.gyoker)
  return bf.maxMelyseg - 1

proc ratlag(bf: LZWBinFa, elem: Csomopont) =
  if elem != nil:
    inc bf.melyseg
    bf.ratlag(elem.jobbEgy)
    bf.ratlag(elem.balNulla)
    dec bf.melyseg
    if elem.jobbEgy == nil and elem.balNulla == nil:
      inc bf.atlagdb
      bf.atlagosszeg += bf.melyseg

proc getAtlag(bf: LZWBinFa): float =
  bf.melyseg = 0
  bf.atlagosszeg = 0
  bf.atlagdb = 0
  bf.ratlag(bf.gyoker)
  if bf.atlagdb > 0:
    bf.atlag = bf.atlagosszeg.float / bf.atlagdb.float
  return bf.atlag

proc rszoras(bf: LZWBinFa, elem: Csomopont) =
  if elem != nil:
    inc bf.melyseg
    bf.rszoras(elem.jobbEgy)
    bf.rszoras(elem.balNulla)
    dec bf.melyseg
    if elem.jobbEgy == nil and elem.balNulla == nil:
      inc bf.atlagdb
      bf.szorasosszeg += pow(bf.melyseg.float - bf.atlag, 2)

proc getSzoras(bf: LZWBinFa): float =
  bf.atlag = bf.getAtlag()
  bf.szorasosszeg = 0.0
  bf.melyseg = 0
  bf.atlagdb = 0
  bf.rszoras(bf.gyoker)
  if bf.atlagdb - 1 > 0:
    bf.szoras = sqrt(bf.szorasosszeg / (bf.atlagdb - 1).float)
  else:
    bf.szoras = sqrt(bf.szorasosszeg)
  return bf.szoras

proc rkiir(bf: LZWBinFa, elem: Csomopont, fs: FileStream) =
  if elem != nil:
    inc bf.melyseg
    bf.rkiir(elem.jobbEgy, fs)
    fs.write(repeat("---", bf.melyseg) & elem.betu & "(" & $(bf.melyseg - 1) & ")\n")
    bf.rkiir(elem.balNulla, fs)
    dec bf.melyseg

proc kiir(bf: LZWBinFa, fs: FileStream) =
  bf.melyseg = 0
  bf.rkiir(bf.gyoker, fs)

proc main() =
  if paramCount() != 3 or paramStr(2) != "-o":
    echo "Usage: lzwtree in_file -o out_file"
    quit(-1)

  let inFile = paramStr(1)
  let outFile = paramStr(3)
  
  var beFile = newFileStream(inFile, fmRead)
  if beFile == nil:
    echo inFile, " nem letezik..."
    quit(-3)

  var kiFile = newFileStream(outFile, fmWrite)
  var bf = ujLZWBinFa()
  var b: uint8

  while beFile.readData(addr b, 1) == 1:
    if b == 0x0a: break

  var kommentben = false
  while beFile.readData(addr b, 1) == 1:
    if b == 0x3e: # '>'
      kommentben = true
      continue
    if b == 0x0a: # újsor
      kommentben = false
      continue
    if kommentben: continue
    if b == 0x4e: # 'N'
      continue

    # Bit léptetés
    for i in 0..7:
      if (b and 0x80) != 0:
        bf << '1'
      else:
        bf << '0'
      b = b shl 1

  bf.kiir(kiFile)
  kiFile.write("depth = ", bf.getMelyseg(), "\n")
  kiFile.write("mean = ", bf.getAtlag(), "\n")
  kiFile.write("var = ", bf.getSzoras(), "\n")

  beFile.close()
  kiFile.close()

main()