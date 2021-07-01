# -*- coding: utf-8 -*-
"""
Created on Thu Jun 17 00:24:37 2021

@author: Sergei
"""

import numpy as np
from nltk.stem.snowball import SnowballStemmer
from nltk import regexp_tokenize
from pymorphy2 import MorphAnalyzer
snowball = SnowballStemmer(language="russian")
morph=MorphAnalyzer()
f = {1: 'один', 2: 'два', 3: 'три', 4: 'четыре', 5: 'пять',
         6: 'шесть', 7: 'семь', 8: 'восемь', 9: 'девять'}

o = {10: 'десять', 20: 'двадцать', 30: 'тридцать', 40: 'сорок',
         50: 'пятьдесят', 60: 'шестьдесят', 70: 'семьдесят',
         80: 'восемьдесят', 90: 'девяносто', 100 : 'сто', 200: 'двести', 300: 'триста',
         400 : 'четыреста', 500: 'пятьсот', 600: 'шестьсот', 700: 'семьсот', 800: 'восемьсот',
         900: 'девятьсот', 1000: 'тысяча', 1000000:'миллион'}
s = {11: 'одиннадцать', 12: 'двенадцать', 13: 'тринадцать',
         14: 'четырнадцать', 15: 'пятнадцать', 16: 'шестнадцать',
         17: 'семнадцать', 18: 'восемнадцать', 19: 'девятнадцать'}

f1 = {list(f.values())[i] : list(f.keys())[i] for i in range(len(f))}
o1 = {list(o.values())[i] : list(o.keys())[i] for i in range(len(o))}
s1 = {list(s.values())[i] : list(s.keys())[i] for i in range(len(s))}

def merge_two_dicts(x, y):
    z = x.copy()   # start with x's keys and values
    z.update(y)    # modifies z with y's keys and values & returns None
    return z

full_dict = merge_two_dicts(merge_two_dicts(f,o),s)
full_dict_i = merge_two_dicts(merge_two_dicts(f1,o1),s1)

def find_bounds(keys):
    bounds = np.zeros_like(np.array(keys))
    try:
        bounds[0] = 1
    except:
        return bounds
    for i in range(1,len(bounds)):
        if keys[i-1]!=keys[i] - 1:
            bounds[i] = 1
    return bounds

def dict_to_numbers(found_numbers):
    keys = list(found_numbers.keys())
    values = list(found_numbers.values())
    res = {}
    i = 0
    bounds = find_bounds(keys)
            
    res = {}
    j = 0
    for i in range(len(values)-1):
        if values[i+1]!=1000 and values[i+1]!=1000000 and bounds[i+1]==0 and values[i]!=1000 and values[i]!=1000000:
            values[i+1] += values[i]
            values[i] = 0
    for i in range(len(bounds)):
        if bounds[i] == 1:
            j = i
            res[keys[j]] = values[j]
            continue
        if bounds[i-1] == 1 and (values[i] == 1000 or values[i] == 1000000):
            res[keys[j]]*=values[i]
        elif (values[i] == 1000 or values[i] == 1000000):
            try:
                res[keys[j]]-=values[i-1]
                res[keys[j]]+=values[i-1]*values[i]
            except:
                pass
        else:
            res[keys[j]]+=values[i]
        
    bounds = np.array(keys)[bounds.astype(bool)]
    return res, bounds
    

    
def words_to_numbers(text_tokenized, orig, digital_dict = full_dict_i):
    found_numbers = {}
    text_processed = text_tokenized.copy()
    for i,word in enumerate(text_tokenized):
        try:
            found_numbers[i] = digital_dict[word]
        except KeyError:
            continue
    res, bounds = dict_to_numbers(found_numbers)
    for j in bounds:
        text_processed[j] = res[j]
    keys = list(found_numbers.keys())
    #print( keys )
    #print( text_processed )
    #print( orig )
    #print( len(text_tokenized), len(orig), len(text_processed) )
    for i in range(len(text_processed)):
        if i in keys:
            if i in bounds:
                continue
            else:
                try:
                    a = int(text_tokenized[i])
                except:
                    text_processed[i] = '~~~'
        else:
            text_processed[i] = orig[i]
    #print( text_processed )
    flag = True
    while flag:
        try:
            text_processed.remove('~~~')
        except:
            flag = False
    #bounds = np.array(keys)[bounds.astype(bool)]
    return text_processed, bounds
    
        
def tokenize_n_normalize_(sent, pat=r"(?u)\b\w\w+\b", morph=MorphAnalyzer()):
   tokens = regexp_tokenize(sent, pat)
   return [morph.parse(tok)[0].normal_form
            for tok in tokens], tokens


def tokenize_n_normalize(sent, pat=r"(?u)\b\w\w+\b", morph=MorphAnalyzer()):
    return [snowball.stem(morph.parse(tok)[0].normal_form)
            for tok in regexp_tokenize(sent, pat)]


def list_to_str(l):
    s = ''
    for a in l:
        if type(a) == int:
            a = str(a)
        s+=a+' '
    s = s[:-1]
    return s

def number_extraction(text):
    
    tnn, orig = tokenize_n_normalize_(text)
    for i in range(len(tnn)):
        text_ = tnn[i]
        text_ = text_.replace('первый','один').replace('второй','два').replace('третий','три').replace('четвертый','четыре')
        text_ = text_.replace('пятый','пять').replace('шестой','шесть').replace('седьмой','семь').replace('восьмой','восемь')
        text_ = text_.replace('девятый','девять').replace('десятый','десять').replace('одиннадцатый','одиннадцать')
        text_ = text_.replace('двенадцатый','двенадцать').replace('тринадцатый','тринадцать').replace('четырнадцатый','четырнадцать')
        text_ = text_.replace('пятнадцатый','пятнадцать').replace('шестнадцатый','шестнадцать').replace('семнадцатый','семнадцать')
        text_ = text_.replace('восемнадцатый','восемнадцать').replace('девятнадцатый','девятнадццать').replace('двадцатый','двадцать')
        text_ = text_.replace('тридцатый','тридцать').replace('сороковой','сорок').replace('пятидесятый','пятьдесят')
        text_ = text_.replace('шестидесятый','шестьдесят').replace('семидесятый','семьдесят').replace('восьмидесятый','восемьдесят')
        text_ = text_.replace('девяностый','девяносто').replace('сотый','сто').replace('двухсотый','двести')
        text_ = text_.replace('трехсотый','триста').replace('четырехсотый','четыреста').replace('пятисотый','пятьсот')
        text_ = text_.replace('щестисотый','шеестьсот').replace('семисотый','семьсот').replace('восьмисотый','восемьсот')
        text_ = text_.replace('девятисотый','девятьсот').replace('тысячный','тысяча')
        tnn[i] = text_
        
    numbered_text, _ = words_to_numbers(tnn, orig)
     
    tagged_numbers = {}
    nums = []
    for i,w in enumerate(numbered_text):
        try:
            num = int(w)
            tagged_numbers[i] = num
            nums.append(num)
        except ValueError:
            continue
    return tagged_numbers, list_to_str(numbered_text)

def number_replace(text):
    TEXT = text.split()
    tagged_numbers,_ = number_extraction(text)
    for place in tagged_numbers.keys():
        TEXT[place+1] = str(tagged_numbers[place])
    tnn, orig = tokenize_n_normalize_(text)
    label = np.zeros_like(TEXT,dtype = int)
    for i in range(len(label)):
        if morph.parse(TEXT[i])[0].normal_form in list(full_dict_i.keys()):
            label[i] = 1
            print(tnn[i],i)
    print(label)
    TEXT_ = []
    for i in range(len(label)):
        if label[i] == 0:
            TEXT_.append(TEXT[i])
    return list_to_str(TEXT_)


    
