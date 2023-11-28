from transformers import pipeline

generator = pipeline('text-generation', model='gpt2')
sample = generator('My name is Barry Allen and I am', pad_token_id=generator.tokenizer.eos_token_id)

print (sample)