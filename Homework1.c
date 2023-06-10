#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELD_LEN 10

const char *csv_adress = "records.csv";
const char *binary_address = "binFile.bin";
void binaryToXml(const unsigned char *binaryData, int dataSize)
{
    FILE *xmlFile = fopen("output.xml", "w");
    if (xmlFile == NULL)
    {
        printf("File opening error!");
        return;
    }

    // Write start of XML
    fprintf(xmlFile, "<root>\n");

    // Export binary data to XML format
    int offset = 0;
    char *data_ptr = (char *)binaryData;

    // Name
    int name_len = strnlen(data_ptr + offset, MAX_FIELD_LEN);
    fprintf(xmlFile, "  <name>%.*s</name>\n", name_len, data_ptr + offset);
    offset += name_len + 1;

    // Surname
    int surname_len = strnlen(data_ptr + offset, MAX_FIELD_LEN);
    fprintf(xmlFile, "  <surname>%.*s</surname>\n", surname_len, data_ptr + offset);
    offset += surname_len + 1;

    // Gender
    fprintf(xmlFile, "  <gender>%c</gender>\n", data_ptr[offset]);
    offset += 1;

    // Occupacy
    int occupacy_len = strnlen(data_ptr + offset, MAX_FIELD_LEN);
    fprintf(xmlFile, "  <occupacy>%.*s</occupacy>\n", occupacy_len, data_ptr + offset);
    offset += occupacy_len + 1;

    // Level of education
    fprintf(xmlFile, "  <level_of_education>%c</level_of_education>\n", data_ptr[offset]);
    offset += 1;

    // Email
    int email_len = strnlen(data_ptr + offset, MAX_FIELD_LEN);
    fprintf(xmlFile, "  <email>%.*s</email>\n", email_len, data_ptr + offset);
    offset += email_len + 1;

    // Bank account number
    int account_num_len = strnlen(data_ptr + offset, MAX_FIELD_LEN);
    fprintf(xmlFile, "  <bank_account_number>%.*s</bank_account_number>\n", account_num_len, data_ptr + offset);
    offset += account_num_len + 1;

    // IBAN
    int iban_len = strnlen(data_ptr + offset, MAX_FIELD_LEN);
    fprintf(xmlFile, "  <IBAN>%.*s</IBAN>\n", iban_len, data_ptr + offset);
    offset += iban_len + 1;

    // Account type
    fprintf(xmlFile, "  <account_type>%c</account_type>\n", data_ptr[offset]);
    offset += 1;

    // Currency unit
    int currency_len = strnlen(data_ptr + offset, MAX_FIELD_LEN);
    fprintf(xmlFile, "  <currency_unit>%.*s</currency_unit>\n", currency_len, data_ptr + offset);
    offset += currency_len + 1;

    // Total balance available
    fprintf(xmlFile, "  <total_balance_available>%c</total_balance_available>\n", data_ptr[offset]);
    offset += 1;

    // Available for loan
    int loan_len = strnlen(data_ptr + offset, MAX_FIELD_LEN);
    fprintf(xmlFile, "  <available_for_loan>%.*s</available_for_loan>\n", loan_len, data_ptr + offset);
    offset += loan_len + 1;

    // Write the end of XML
    fprintf(xmlFile, "</root>\n");

    fclose(xmlFile); // Close file
}

int main()
{   
    
    FILE *csv_file = fopen(csv_adress, "r");  
    if (csv_file == NULL)
    {
        printf("An error occurred while opening the CSV file.\n");
        return 1;
    }

    FILE *binary_file = fopen(binary_address, "wb");
    if (binary_file == NULL)
    {
        printf("An error occurred while opening the binary file.\n");
        return 1;
    }

    char line[256];
    char *part;
    fgets(line, sizeof(line), csv_file);
    while (fgets(line, sizeof(line), csv_file))
    {
        part = strtok(line, ",");
        while (part != NULL)
        {
            int length = strlen(part);
            if (length == 1) // If it is letter
            {
                fwrite(part, sizeof(char), 1, binary_file);
            }
            else // If it is word
            {
                for (int i = 0; i < length; i++)
                {
                    fwrite(&part[i], sizeof(char), 1, binary_file);
                }
            }

            // Add space between blocks
            fwrite(" ", sizeof(char), 1, binary_file);

            part = strtok(NULL, ",");
        }
    }

    fclose(binary_file);

    binary_file = fopen("binFile.bin", "rb");
    // Process data by reading binary file
    fseek(binary_file, 0, SEEK_END);
    int dataSize = ftell(binary_file);
    fseek(binary_file, 0, SEEK_SET);
    unsigned char *binaryData = (unsigned char *)malloc(dataSize);
    fread(binaryData, 1, dataSize, binary_file);

    // Export binary data to XML format
    binaryToXml(binaryData, dataSize);

    free(binaryData); // Clear memory

    fclose(csv_file);
    fclose(binary_file);

    printf("CSV file is written in binary format.\n");

    return 0;
}


