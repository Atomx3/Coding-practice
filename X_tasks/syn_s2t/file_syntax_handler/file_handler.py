"""
This module contains functions for handling different file formats.
It uses specific libraries to parse syntax markers
"""
import os
import re
from enum import Enum
import markdown
import yaml
from bs4 import BeautifulSoup
import xml.etree.ElementTree as ET

# --- Define File Formats ---
class FileFormat(Enum):
    MARKDOWN = ".md"
    YAML = ".yaml"
    XML = ".xml"
    HTML = ".html"
    TEXT = ".txt"
    UNKNOWN = "unknown"

def get_file_format(filename):
  """Determines the file format based on the file extension."""
  _, ext = os.path.splitext(filename)
  if ext == FileFormat.MARKDOWN.value:
    return FileFormat.MARKDOWN
  elif ext == FileFormat.YAML.value:
    return FileFormat.YAML
  elif ext == FileFormat.XML.value:
    return FileFormat.XML
  elif ext == FileFormat.HTML.value:
    return FileFormat.HTML
  elif ext == FileFormat.TEXT.value:
      return FileFormat.TEXT
  else:
    return FileFormat.UNKNOWN


def extract_translatable_text(text, file_format):
    """Extracts translatable text using parsing libraries."""
    if file_format == FileFormat.MARKDOWN:
        try:
            html = markdown.markdown(text)
            soup = BeautifulSoup(html, 'html.parser')
            parts = []
            for element in soup.recursiveChildGenerator():
                if element.name == "code" or element.name == "img":
                    parts.append((False, str(element)))
                elif isinstance(element, str):
                    parts.append((True, element))
            return parts
        except Exception as e:
            return [(True, text)]
    elif file_format == FileFormat.YAML:
        try:
            data = yaml.safe_load(text)
            parts = []
            for key, value in data.items():
                if isinstance(value, str):
                    parts.append((True, value))
                elif isinstance(value, (int, float, bool)):
                    parts.append((False, str(value)))
                elif isinstance(value, (list, dict)):
                    parts.append((False, str(value)))
            return parts
        except Exception as e:
            return [(True, text)]
    elif file_format == FileFormat.XML:
        try:
            tree = ET.fromstring(text)
            parts = []
            for element in tree.iter():
                if element.text:
                    parts.append((True, element.text))
            return parts
        except Exception as e:
           return [(True, text)]
    elif file_format == FileFormat.HTML:
         try:
             soup = BeautifulSoup(text, 'html.parser')
             parts = []
             for element in soup.recursiveChildGenerator():
                 if isinstance(element, str):
                     parts.append((True, element))
                 else:
                     if element.name in ['script', 'style', 'code', 'img']:
                         parts.append((False, str(element)))
             return parts
         except Exception as e:
            return [(True, text)]
    else:
        return [(True, text)]


def reconstruct_translated_text(original_parts, translated_text):
    """Reconstructs the translated text based on the original structure."""
    translated_parts = translated_text.split('\n')  # Split by newline
    result = []
    translated_index = 0
    for is_translatable, original_part in original_parts:
        if is_translatable:
            if translated_index < len(translated_parts):
                result.append(translated_parts[translated_index])
                translated_index += 1
            else:
                # Handle cases where translation might be shorter than original
                result.append("") # Add an empty string if no translation available.
        else:
            result.append(original_part)
    return "".join(result)  
