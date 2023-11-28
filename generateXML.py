from transformers import GPT2LMHeadModel, GPT2Tokenizer

# Load pre-trained GPT-2 model and tokenizer

tokenizer = GPT2Tokenizer.from_pretrained("gpt2")
model = GPT2LMHeadModel.from_pretrained("gpt2", pad_token_id=tokenizer.eos_token_id)

#Example XML file
example_xml = """
<schedule>
    <lecture>
    <topic>Testing Overview</topic>
    <instructor>Qian Zhang</instructor>
    <time>Week 1</time>
  </lecture>
  <lecture>
    <topic>Input Space Partitioning</topic>
    <instructor>Qian Zhang</instructor>
    <time>Week 2</time>
  </lecture>
  <lecture>
    <topic>Test Coverage</topic>
    <instructor>Qian Zhang</instructor>
    <time>Week 3</time>
  </lecture>
</schedule>"""

# Set the prompt for XML content generation
prompt = example_xml + "is an XML file. Generate another xml file."

# Generate XML content using GPT-2
generated_text = model.generate(
    tokenizer.encode(prompt, return_tensors="pt"),
    max_length=500,
    num_beams=2,
    no_repeat_ngram_size=3,
    top_k=50,
    pad_token_id=tokenizer.eos_token_id,
)

# Decode the generated text
generated_xml = tokenizer.decode(generated_text[0], skip_special_tokens=True)

print(generated_xml)