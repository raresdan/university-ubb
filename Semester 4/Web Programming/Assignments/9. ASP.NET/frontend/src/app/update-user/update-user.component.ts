import { Component, OnInit } from '@angular/core';
import {UserService} from '../user.service';
import {ActivatedRoute, Router, RouterLink} from '@angular/router';
import { FormBuilder, FormGroup, ReactiveFormsModule, Validators } from '@angular/forms';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-update-user',
  standalone: true,
  imports:[
    CommonModule,
    ReactiveFormsModule,
    RouterLink
  ],
  templateUrl: './update-user.component.html',
  styleUrls: ['./update-user.component.css']
})
export class UpdateUserComponent implements OnInit {
  id: string = '';
  updateUserForm: FormGroup = new FormGroup({});
  constructor(private formBuilder: FormBuilder, private service: UserService, private router: Router, private route: ActivatedRoute) { }

  ngOnInit(): void {
    this.initializeForm();
    this.id = this.route.snapshot.queryParams['id'];
    this.service.getUserData(this.id).subscribe((user) => {
    this.updateUserForm.patchValue({
      id: this.id,
      name: user.name,
      username: user.username,
      password: user.password,
      age: user.age,
      role: user.role,
      email: user.email,
      webpage: user.webpage
    });
  });
  }

  initializeForm() {
    this.updateUserForm = this.formBuilder.group({
      id: [null],
      name: ['', Validators.required],
      username: [{value: '', disabled: true}, Validators.required],
      password: ['', Validators.required],
      age: [null],
      role: [''],
      email: [{value: '', disabled: true}, Validators.required ],
      webpage: ['']
    });
  }

  updateUser(): void {
    this.service.updateUser(this.id, this.updateUserForm.value).subscribe({
      next: response => {
          this.router.navigate(['/users']);
        console.log('User updated successfully', response);
      },
      error: error => {
        console.error('There was an error!', error);
      }
    });
  }

  onSubmit(): void {
    if (this.updateUserForm.invalid) {
      console.log('Invalid form');
      return;
    }
    console.log('Updating user');
    this.updateUser();
  }

}
