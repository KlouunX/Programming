# frozen_string_literal: true

subscribers = %w[5553457867 5417890987 5524567867 5356789865 5321234567 5546754321 5389876543]

monthly_price = [120, 50, 500, 70, 50, 67, 99] # Tiplere (tamsayı) dikkat

starred_customer = [true, false, true, true, false, false, true]

def telephone_no_to_customer_index(subscribers, telephone_no) # Telefon numarasına karşı düşen müşteri indisi
  subscribers.find_index(telephone_no)
end

def starred_customer?(starred_customer, customer_index) # İndisli müşterinin indirim hakkı var mı?
  starred_customer[customer_index] if customer_index != nil
end

# İndirimi ilgili indeksli müşteriye uygulayarak monthly_price dizisini güncelle.
def apply_discount(monthly_price, customer_index, discount_amount)
  return if customer_index == nil

  monthly_price[customer_index] - (monthly_price[customer_index] * discount_amount.to_f / 100)
end

print '<tel_no> INDRIM<miktar> giriniz: '
telephone_no, discount_amount = gets.chomp.split # Telefon numarası ve indirim miktarını al

if (telephone_no && discount_amount) != nil && (discount_amount.include? "INDIRIM")
  discount_amount = discount_amount.match(/INDIRIM(\d{2})/).values_at(1)[0]

  customer_index = telephone_no_to_customer_index(subscribers, telephone_no)
  starred_or_not = starred_customer?(starred_customer, customer_index)
  useDiscount = apply_discount(monthly_price, customer_index, discount_amount)

  if customer_index != nil
    puts 'STATUS: VALID'
  else
    puts 'STATUS: INVALID'
  end

  if starred_or_not == true
    puts "DISCOUNT: POSSIBLE\n#{telephone_no} UPDATED  PRICE #{monthly_price[customer_index]} TO #{useDiscount}"
  elsif starred_or_not == false
    puts "DISCOUNT: NOT POSSIBLE\n#{telephone_no} PRICE #{monthly_price[customer_index]}"
  end

else
  puts 'STATUS: ERROR'
end
